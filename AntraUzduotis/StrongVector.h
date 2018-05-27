//
// Created by augus on 18/05/26.
//

#ifndef STRONGVECTOR_STRONGVECTOR_H
#define STRONGVECTOR_STRONGVECTOR_H


#include <memory>
#include <algorithm>
#include <cassert>

template<typename T, typename Alloc>
class VBase{
public:
    typedef typename std::allocator_traits<Alloc>::template
            rebind_alloc<T> alloc_type;
    typedef typename std::allocator_traits<alloc_type>::pointer pointer;

    class VImpl : public alloc_type{
    public:
        pointer elemStart;
        pointer elemEnd;
        pointer elemCap;
        VImpl() : alloc_type(), elemStart(), elemEnd(), elemCap(){}

        explicit VImpl(alloc_type const& a) noexcept : alloc_type(a), elemStart(), elemEnd(), elemCap(){}
        explicit VImpl(alloc_type&& a) noexcept : alloc_type(std::move(a)), elemStart(), elemEnd(), elemCap(){}
        void keitimas(VImpl& x){
            auto t = x.elemStart;
            x.elemStart = elemStart;
            elemStart = t;

            t = x.elemEnd;
            x.elemEnd = elemEnd;
            elemEnd = t;

            t = x.elemCap;
            x.elemCap = elemCap;
            elemCap = t;
        }
    };

    typedef Alloc allocator_type;

    alloc_type& get_alloc() noexcept { return *static_cast<alloc_type*>(&this->implementacija); }
    const alloc_type& get_alloc() const noexcept { return *static_cast<const alloc_type*>(&this->implementacija);}
    allocator_type get_allocator() const noexcept { return allocator_type(get_alloc()); }

    VBase() : implementacija(){}

    explicit VBase(const alloc_type& a) : implementacija(a){}

    explicit VBase(std::size_t n) : implementacija(){ create_storage(n); }
    VBase(std::size_t n, const allocator_type& a) : implementacija(a){ create_storage(n);}

    explicit VBase(alloc_type&& a) : implementacija(std::move(a)){}
    VBase(VBase&& x) noexcept : implementacija(std::move(x.get_alloc())){this->implementacija.keitimas(x.implementacija);}
    VBase(VBase&& x, const allocator_type& a) : implementacija(a){
        if (x.get_allocator() == a) this->implementacija.keitimas(x.implementacija);
        else{
            std::size_t n = std::distance(x.implementacija.elemStart, x.implementacija.elemEnd);
            create_storage(n);
        }
    }

    ~VBase() noexcept {
        deallocate(this->implementacija.elemStart, std::distance(this->implementacija.elemStart, this->implementacija.elemCap));
    }

public:
    VImpl implementacija;
    pointer allocate(std::size_t n){
        typedef std::allocator_traits<alloc_type> Tal;
        return n != 0 ? Tal::allocate(implementacija, n) : pointer();
    }
    void deallocate(pointer p, std::size_t n){
        typedef std::allocator_traits<alloc_type> Tal;
        if (p){
            Tal::deallocate(implementacija, p, n);
        }
    }

private:
    void create_storage(std::size_t n){
        this->implementacija.elemStart = this->allocate(n);
        this->implementacija.elemEnd = this->implementacija.elemStart;
        this->implementacija.elemCap = this->implementacija.elemStart + n;
    }
};


template<typename T, typename Allocator = std::allocator<T>>
class StrongVector : protected VBase<T, Allocator>{
    typedef VBase<T, Allocator> Base;
    typedef typename Base::alloc_type alloc_type;
    typedef __gnu_cxx::__alloc_traits<alloc_type> Allocator_traits;
public:

    typedef T value_type;
    typedef Allocator allocator_type;
    typedef std::size_t					size_type;
    typedef std::ptrdiff_t					difference_type;
    typedef typename Base::pointer pointer;
    typedef typename Allocator_traits::const_pointer const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef __gnu_cxx::__normal_iterator<pointer, StrongVector> iterator;
    typedef __gnu_cxx::__normal_iterator<const_pointer, StrongVector> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

protected:
    using Base::allocate;
    using Base::deallocate;
    using Base::implementacija;
    using Base::get_alloc;
public:
    // c-tor ir d-tor
    StrongVector() noexcept(std::is_nothrow_default_constructible<allocator_type>::value) : Base(){}
    explicit StrongVector(const allocator_type& a) : Base(a) {}
    explicit StrongVector(size_type n, const allocator_type& a = allocator_type()) : Base(n, a){init(n); }
    StrongVector(size_type n, const value_type& value, const allocator_type& a = allocator_type()) : Base(n, a){ fill_init(n,value);}
    StrongVector(const StrongVector& x) : Base(x.size(), Allocator_traits::select_on_container_copy_construction(x.get_alloc())) {
        this->implementacija.elemEnd = std::__uninitialized_copy_a(x.begin(), x.end(), this->implementacija.elemStart, get_alloc());
    }
    StrongVector(StrongVector&& x) noexcept : Base(std::move(x)) {}
    StrongVector(const StrongVector& x, const allocator_type& a) : Base(x.size(), a){
        this->implementacija.elemEnd = std::__uninitialized_copy_a(x.begin(), x.end(), this->implementacija.elemStart, get_alloc());
    }
    StrongVector(StrongVector&& x, const allocator_type a) noexcept (Allocator_traits::allocator_type::is_always_equal()): Base(std::move(x), a){
        if (x.get_allocator() != a){
            this->implementacija.elemEnd = std::__uninitialized_move_a(x.begin(),x.end(),this->implementacija.elemStart,get_alloc());
            x.clear();
        }
    }
    StrongVector(std::initializer_list<value_type> l, const allocator_type& a = allocator_type()) : Base(a){
        range_init(l.begin(), l.end(), std::random_access_iterator_tag());
    }
    template<typename InputIterator, typename = std::_RequireInputIter<InputIterator>> StrongVector(InputIterator first, InputIterator last, const allocator_type& a = allocator_type()) : Base(a) {
        const auto n = std::distance(first,last);
        implementacija.elemStart = allocateAndCopy(n, first, last);
        implementacija.elemEnd = implementacija.elemStart + n;
        implementacija.elemCap = implementacija.elemStart + n;
    }
    ~StrongVector() noexcept {
        if (!std::is_same<T, std::string>::value) std::_Destroy(this->implementacija.elemStart,this->implementacija.elemEnd, get_alloc());
    }

    // Operator= ir Assignment
    StrongVector& operator= (const StrongVector& x){
        deallocate(this->implementacija.elemStart, size());
        this->implementacija.elemStart = allocate(x.size());
        this->implementacija.elemCap = this->implementacija.elemStart;
        this->implementacija.elemEnd = std::__uninitialized_copy_a(x.implementacija.elemStart,x.implementacija.elemEnd,this->implementacija.elemStart,get_alloc());
        return *this;
    }
    StrongVector& operator= (StrongVector&& x) noexcept{
        deallocate(this->implementacija.elemStart, size());
        this->implementacija.elemStart = allocate(x.size());
        this->implementacija.elemCap = this->implementacija.elemStart;
        this->implementacija.elemEnd = std::__uninitialized_move_a(x.implementacija.elemStart,x.implementacija.elemEnd,this->implementacija.elemStart,get_alloc());
        x.clear();
        return *this;
    }
    StrongVector& operator= (std::initializer_list<value_type> l){
        deallocate(this->implementacija.elemStart, size());
        this->implementacija.elemStart = allocate(l.size());
        this->implementacija.elemCap = this->implementacija.elemStart;
        this->implementacija.elemEnd = std::__uninitialized_move_a(l.begin(),l.end(),this->implementacija.elemStart,get_alloc());
        return *this;
    }

    void assign(size_type n, const value_type& val) {
        deallocate(this->implementacija.elemStart, size());
        this->implementacija.elemStart = allocate(n);
        this->implementacija.elemCap = this->implementacija.elemStart;
        this->implementacija.elemEnd = std::__uninitialized_fill_n_a(this->implementacija.elemStart, n, val, get_alloc());
    }
    template<typename InputIterator, typename = std::_RequireInputIter<InputIterator>> void assign(InputIterator first, InputIterator last) {
        auto n = last - first;
        deallocate(this->implementacija.elemStart, size());
        this->implementacija.elemStart = allocate(n);
        this->implementacija.elemCap = this->implementacija.elemStart;
        this->implementacija.elemEnd = std::__uninitialized_copy_a(first,last,this->implementacija.elemStart,get_alloc());
    }
    void assign(std::initializer_list<value_type> l){
        deallocate(this->implementacija.elemStart, size());
        this->implementacija.elemStart = allocate(l.size());
        this->implementacija.elemCap = this->implementacija.elemStart;
        this->implementacija.elemEnd = std::__uninitialized_move_a(l.begin(),l.end(),this->implementacija.elemStart,get_alloc());
    }

    using Base::get_allocator;

    //iterators
    iterator begin() noexcept { return iterator(this->implementacija.elemStart); }
    const_iterator begin() const { return const_iterator(this->implementacija.elemStart);}
    iterator end() { return iterator(this->implementacija.elemEnd); }
    const_iterator end() const { return const_iterator(this->implementacija.elemEnd); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end());}
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end());}
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    size_type size() const noexcept { return size_type(this->implementacija.elemEnd - this->implementacija.elemStart); }
    size_type max_size() const { return Allocator_traits::max_size(get_alloc()); }
    void resize(size_type new_size){
        if (new_size > size()) {
            if (new_size > max_size()) throw std::length_error("Vector::resize(size_type count)");
            if (new_size > capacity()) {
                pointer t;
                std::copy(this->implementacija.elemStart, this->implementacija.elemEnd, t);
                deallocate(this->implementacija.elemStart, size());
                this->implementacija.elemStart = allocate(new_size);
                this->implementacija.elemCap = this->implementacija.elemStart + new_size;
                this->implementacija.elemEnd = std::__uninitialized_move_a(t, t + size(), this->implementacija.elemStart, get_alloc());
                this->implementacija.elemEnd = std::__uninitialized_default_n_a(this->implementacija.elemEnd, new_size - size(), get_alloc());
            } else {
                this->implementacija.elemEnd = std::__uninitialized_default_n_a(this->implementacija.elemEnd, new_size - size(), get_alloc());
            }
        }
        else if (new_size < size())
            eraseTillEnd(this->implementacija.elemStart + new_size);
    }
    void resize(size_type new_size, const value_type& x){
        if (new_size > size()) {
            if (new_size > max_size()) throw std::length_error("Vector::resize(size_type count)");
            if (new_size > capacity()) {
                pointer t;
                std::copy(this->implementacija.elemStart, this->implementacija.elemEnd, t);
                deallocate(this->implementacija.elemStart, size());
                this->implementacija.elemStart = allocate(new_size);
                this->implementacija.elemCap = this->implementacija.elemStart + new_size;
                this->implementacija.elemEnd = std::__uninitialized_move_a(t, t + size(), this->implementacija.elemStart, get_alloc());
                this->implementacija.elemEnd = std::__uninitialized_fill_n_a(this->implementacija.elemEnd, new_size - size(), x, get_alloc());
            } else {
                this->implementacija.elemEnd = std::__uninitialized_fill_n_a(this->implementacija.elemEnd, new_size - size(), x, get_alloc());
            }
        }
        else if (new_size < size())
            eraseTillEnd(this->implementacija.elemStart + new_size);
    }
    void shrink_to_fit() {}
    size_type capacity() const noexcept { return size_type(this->implementacija.elemCap - this->implementacija.elemStart);}
    bool empty() const noexcept { return begin() == end(); }
    void reserve(size_type n){
        if (n > max_size()) std::__throw_length_error("Vector::reserve");
        if (capacity() < n){
            const  size_type old_size = size();
            pointer t = allocateAndCopy(n, std::__make_move_if_noexcept_iterator(this->implementacija.elemStart), std::__make_move_if_noexcept_iterator(this->implementacija.elemEnd));
            std::_Destroy(this->implementacija.elemStart, this->implementacija.elemEnd, get_alloc());
            deallocate(this->implementacija.elemStart, std::distance(this->implementacija.elemStart, this->implementacija.elemCap));
            this->implementacija.elemStart = t;
            this->implementacija.elemEnd = t + old_size;
            this->implementacija.elemCap = this->implementacija.elemStart + n;
        }
    }

    // references
    reference operator[](size_type n) {
        return *(this->implementacija.elemStart + n);
    }
    const_reference operator[](size_type n) const {
        return *(this->implementacija.elemStart + n);
    }
    reference at(size_type n){
        if (n >= this->size()) std::__throw_out_of_range("StrongVector::at(size_type n)");
        return (*this)[n];
    }
    const_reference at(size_type n) const {
        if (n >= this->size()) std::__throw_out_of_range("StrongVector::at(size_type n)");
        return (*this)[n];
    }
    reference front() noexcept { return *begin();}
    const_reference front() const noexcept { return *begin();}
    reference back() noexcept { return *(end() - 1);}
    const_reference back() const noexcept { return *(end() - 1);}
    T* data() noexcept { return data_ptr(this->implementacija.elemStart); }
    const T* data() const noexcept { return data_ptr(this->implementacija.elemStart); }

    // mods
    void push_back(const value_type& x){
        if (this->implementacija.elemEnd != this->implementacija.elemCap){
            Allocator_traits::construct(this->implementacija, this->implementacija.elemEnd, x);
            this->implementacija.elemEnd++;
        } else real_insert(end(), x);
    }
    void push_back(value_type&& x) { emplace_back(std::move(x));}

    template<typename... Args> reference emplace_back(Args&&... args){
        if (this->implementacija.elemEnd != this->implementacija.elemCap) {
            Allocator_traits::construct(this->implementacija, this->implementacija.elemEnd, std::forward<Args>(args)...);
            this->implementacija.elemEnd++;
        } else real_insert(end(), std::forward<Args>(args)...);
        return back();
    }
    void pop_back(){
        __glibcxx_requires_nonempty();
        this->implementacija.elemEnd--;
        if (!std::is_same<T, std::string>::value) Allocator_traits::destroy(this->implementacija,this->implementacija.elemEnd);
        else (*this->implementacija.elemEnd).~T();
    }

    template<typename... Args> iterator emplace(const_iterator position, Args&&... args){
        if (size() + 1 > max_size()) std::__throw_length_error("Vector::emplace()");
        difference_type posID = position - begin();
        auto old_sz = std::distance(this->implementacija.elemStart, this->implementacija.elemEnd);
        pointer t = new value_type[old_sz + 1];
        if(posID != 0) std::uninitialized_copy(this->implementacija.elemStart, this->implementacija.elemStart + posID, t);
        Allocator_traits::construct(this->implementacija, t + posID, args...);
        std::uninitialized_copy(this->implementacija.elemStart + posID, this->implementacija.elemStart + old_sz, t + posID + 1);
        if (old_sz + 1 > capacity()){
            deallocate(this->implementacija.elemStart, size());
            this->implementacija.elemStart = allocate(old_sz + 1);
            this->implementacija.elemCap = this->implementacija.elemStart + old_sz + 1;
        }
        std::uninitialized_copy(t, t + old_sz + 1, this->implementacija.elemStart);
        this->implementacija.elemEnd = this->implementacija.elemStart + old_sz + 1;
    }

    iterator insert(const_iterator position, const value_type& x){
        const size_type n = position - begin();
        if (this->implementacija.elemStart != this->implementacija.elemEnd){
            if (position == end()){
                Allocator_traits::construct(implementacija, implementacija.elemEnd, x);
                implementacija.elemEnd++;
            }else {
                Temp_value x1(this, x);
                base_insert(position,std::move(x1.val()));
            }
        } else real_insert(begin() + n, x);
        return begin() + n;
    }
    iterator insert(const_iterator position, value_type&& x) {
        const auto n = std::distance(begin(),position);
        if (implementacija.elemEnd != implementacija.elemCap){
            if (position == end()){
                Allocator_traits::construct(implementacija, implementacija.elemEnd, std::move(x));
                implementacija.elemEnd++;
            }
            else base_insert(begin() + n, std::move(x));
        } else real_insert(begin() + n, std::move(x));
        return begin() + n;
    }
    iterator insert(const_iterator position, std::initializer_list<value_type> l){
        auto n = std::distance(begin(), position);
        range_insert(begin() + n, l.begin(), l.end(), std::random_access_iterator_tag());
        return begin()+n;
    }
    iterator insert(const_iterator position, size_type n, const value_type& x) {
        auto posID = std::distance(begin(), position);
        fill_insert(begin()+posID, n, x);
        return begin() + posID;
    }
    template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>> iterator insert(const_iterator position, _InputIterator first, _InputIterator last) {
        auto posID = std::distance(begin(), position);
        insert_dis(begin()+ posID, first, last, std::false_type());
        return begin() + posID;
    }

    iterator erase(const_iterator position) { return _erase(begin() + (position - begin())); }
    iterator erase( const_iterator first, const_iterator last ) { return _erase(begin() + (first - begin()), begin() + (last - begin())); }

    void swap(StrongVector& x) noexcept{
        assert(get_alloc() == x.get_alloc() || Allocator_traits::_S_propagate_on_swap());
        this->implementacija.keitimas(x.implementacija);
        Allocator_traits::_S_on_swap(get_alloc(), x.get_alloc());
    }
    void clear(){ eraseTillEnd(implementacija.elemStart); }

protected:

    class Temp_value{
        typename std::aligned_storage<sizeof(T), alignof(T)>::type buf;
        StrongVector* sv;
        pointer ptr() { return std::pointer_traits<pointer>::pointer_to(val()); }
    public:
        value_type& val() { return *reinterpret_cast<T*>(&buf); }
        template <typename... Args> explicit Temp_value(StrongVector* vec, Args&&... args) : sv(vec){
            Allocator_traits::construct(sv->implementacija, ptr(), std::forward<Args>(args)...);
        }
        ~Temp_value(){
            if (!std::is_same<T, std::string>::value){
                Allocator_traits::destroy(sv->implementacija,ptr());
            }
        }
    };


    template<typename ForwardIterator> pointer allocateAndCopy(size_type n, ForwardIterator first, ForwardIterator last){
        pointer new_elem = this->allocate(n);
        try {
            std::__uninitialized_copy_a(first,last,new_elem, get_alloc());
            return new_elem;
        }
        catch (...) {
            deallocate(new_elem, n);
            throw;
        }

    }

    template<typename Integer> void init_dis(Integer n, Integer value, std::true_type){
        this->implementacija.elemStart = allocate(static_cast<size_type>(n));
        this->implementacija.elemCap = this->implementacija.elemStart + static_cast<size_type>(n);
        fill_init(static_cast<size_type>(n), value);
    }
    template<typename InputIterator> void init_dis(InputIterator first, InputIterator last, std::false_type){
        typedef typename std::iterator_traits<InputIterator>::iterator_category IterCategory;
        range_init(first, last, IterCategory());
    }
    template<typename InputIterator> void range_init(InputIterator first, InputIterator last, std::input_iterator_tag){
        for (auto i = first; i != last; ++i){
            emplace_back(*i);
        }
    }
    template<typename ForwardIterator> void range_init (ForwardIterator first, ForwardIterator last, std::forward_iterator_tag){
        const size_type n = std::distance(first, last);
        this->implementacija.elemStart = this->allocate(n);
        this->implementacija.elemCap = this->implementacija.elemStart + n;
        this->implementacija.elemEnd = std::__uninitialized_copy_a(first,last,this->implementacija.elemStart, get_alloc());
    }
    inline void fill_init (size_type n, const value_type& value){
        this->implementacija.elemEnd = std::__uninitialized_fill_n_a(this->implementacija.elemStart, n, value, get_alloc());
        this->implementacija.elemCap = this->implementacija.elemStart + n;
    }
    inline void init (size_type n){
        this->implementacija.elemEnd = std::__uninitialized_default_n_a(this->implementacija.elemStart, n, get_alloc());
    }

    template<typename Args> void base_insert(iterator pos, Args args){
        Allocator_traits::construct(implementacija, implementacija.elemEnd, std::move(*(this->implementacija.elemEnd - 1)));
        implementacija.elemEnd++;
        std::move_backward(pos, implementacija.elemEnd - 2, implementacija.elemEnd - 1);
        *pos = std::forward<Args>(args);
    }
    template<typename... Args> iterator base_insert(const_iterator pos, Args&&... args){
        const auto n = pos - begin();
        if (implementacija.elemEnd != implementacija.elemCap)
            if (pos == end()){
                Allocator_traits::construct(implementacija, implementacija.elemEnd, std::forward<Args>(args)...);
                implementacija.elemEnd++;
            } else {
                Temp_value x1(this, std::forward<Args>(args)...);
                base_insert(begin() + n, std::move(x1.val()));
            }
        else real_insert(begin() + n, std::forward<Args>(args)...);
        return begin() + n;
    }

    template<typename... Args> void real_insert(iterator pos, Args&&... args){
        auto sz = check_lenght(1);
        auto posID = std::distance(begin(), pos);
        pointer tempS(allocate(sz));
        pointer tempF = pointer();
        try {

            tempF = std::__uninitialized_move_if_noexcept_a(implementacija.elemStart, pos.base(), tempS, get_alloc());
            Allocator_traits::construct(implementacija, tempS + posID, std::forward<Args>(args)...);
            tempF++;
            tempF = std::__uninitialized_move_if_noexcept_a(pos.base(), implementacija.elemEnd, tempF, get_alloc());

        } catch (...) {

            if (!tempF) Allocator_traits::destroy(implementacija, tempS + posID);
            else std::_Destroy(tempS, tempF, get_alloc());
            deallocate(tempS, sz);
            throw;

        }
        std::_Destroy(implementacija.elemStart, implementacija.elemEnd, get_alloc());
        deallocate(implementacija.elemStart, std::distance(implementacija.elemStart, implementacija.elemCap));
        implementacija.elemStart = tempS;
        implementacija.elemEnd = tempF;
        implementacija.elemCap = tempS + sz;
    }
    void fill_insert(iterator pos, size_type n, const value_type& x){

        if (n!=0){
            if (std::distance(implementacija.elemEnd, implementacija.elemCap) >= n){
                Temp_value x1(this, x);
                value_type& xcopy = x1.val();
                const size_type posID = std::distance(pos,end());
                pointer tempF(implementacija.elemEnd);
                if (posID > n){
                    std::__uninitialized_move_a(implementacija.elemEnd - n, implementacija.elemEnd, implementacija.elemEnd, get_alloc());
                    implementacija.elemEnd += n;
                    std::move_backward(pos.base(), tempF - n, tempF);
                    std::fill(pos, pos + n, xcopy);
                } else{
                    implementacija.elemEnd = std::uninitialized_fill_n(implementacija.elemEnd, n - posID, xcopy);
                    std::__uninitialized_move_a(pos.base(), tempF, implementacija.elemEnd, get_alloc());
                    implementacija.elemEnd += posID;
                    std::fill(pos.base(), tempF, xcopy);
                }
            } else{
                const size_type sz = check_lenght(n);
                pointer tempS(allocate(sz));
                const size_type posID = std::distance(begin(), pos);
                pointer tempF(tempS);
                try {
                    std::uninitialized_fill_n(tempS + posID, n, x);
                    tempF = pointer();
                    tempF = std::__uninitialized_move_if_noexcept_a(implementacija.elemStart, pos.base(), tempS, get_alloc());
                    tempF += n;
                    tempF = std::__uninitialized_move_if_noexcept_a(pos.base(), implementacija.elemEnd, tempF, get_alloc());
                }catch (...){
                    if (!tempF) std::_Destroy(tempS + posID, tempS + posID + n, get_alloc());
                    else std::_Destroy(tempS, tempF, get_alloc());
                    deallocate(tempS, sz);
                    throw;
                }
                std::_Destroy(implementacija.elemStart, implementacija.elemEnd, get_alloc());
                deallocate(implementacija.elemStart, capacity());
                implementacija.elemStart = tempS;
                implementacija.elemEnd = tempF;
                implementacija.elemCap = tempS + sz;
            }
        }
    }
    template<typename InputIterator> void range_insert(iterator pos, InputIterator first, InputIterator last, std::input_iterator_tag){
        for (auto i = first; i != last ; i++) {
            pos = insert(pos, *i);
            pos++;
        }
    }
    template<typename ForwardIterator> void range_insert(iterator pos, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) {
        if (first != last){
            const size_type n = std::distance(first,last);
            if (std::distance(implementacija.elemEnd, implementacija.elemCap) >= n){
                const size_type posID = std::distance(pos,end());
                pointer tempF(implementacija.elemEnd);
                if (posID > n){
                    std::__uninitialized_move_a(implementacija.elemEnd - n, implementacija.elemEnd, implementacija.elemEnd, get_alloc());
                    implementacija.elemEnd += n;
                    std::move_backward(pos.base(), tempF - n, tempF);
                    std::copy(first, last, pos);
                } else{
                    ForwardIterator m = first;
                    std::advance(m, posID);
                    std::__uninitialized_copy_a(m, last, implementacija.elemEnd, get_alloc());
                    implementacija.elemEnd += n - posID;
                    std::__uninitialized_move_a(pos.base(), tempF, implementacija.elemEnd, get_alloc());
                    implementacija.elemEnd += posID;
                    std::copy(first, m, pos);
                }
            } else{
                const size_type sz = check_lenght(n);
                pointer tempS(allocate(sz));
                pointer tempF(tempS);
                try {
                    tempF = std::__uninitialized_move_if_noexcept_a(implementacija.elemStart, pos.base(), tempS, get_alloc());
                    tempF = std::__uninitialized_copy_a(first, last, tempF, get_alloc());
                    tempF = std::__uninitialized_move_if_noexcept_a(pos.base(), implementacija.elemEnd, tempF, get_alloc());
                } catch (...){
                    std::_Destroy(tempS, tempF, get_alloc());
                    deallocate(tempS, sz);
                    throw;
                }
                std::_Destroy(implementacija.elemStart, implementacija.elemEnd, get_alloc());
                deallocate(implementacija.elemStart, capacity());
                implementacija.elemStart = tempS;
                implementacija.elemEnd = tempF;
                implementacija.elemCap = tempS + sz;
            }
        }
    }


    void eraseTillEnd(pointer pos){
        get_alloc().destroy(pos,this,implementacija.elemEnd);
        this->implementacija.elemEnd = pos;
    }
    iterator _erase(iterator position){
        std::copy(position + 1, end(), position);
        this->implementacija.elemEnd--;
        return position;
    }
    iterator _erase(iterator first, iterator last){
        auto n = std::distance(first,last);
        std::copy(last, end(), first);
        this->implementacija.elemEnd -= n;
        return first;
    }

    size_type check_lenght(size_type n){
        if (max_size() - size() < n) std::__throw_length_error("Lenght is too big!");
        const size_type i = size() + std::max(size(), n);
        return (i < size() || i > max_size()) ? max_size() : i;
    }



private:
    void move_assign(StrongVector&& x) noexcept{
        this->implementacija.keitimas(x.implementacija);
        std::__alloc_on_move(get_alloc(), x.get_alloc());
        x.clear();
    }
    void move_assign_v2(StrongVector&& x, std::false_type) noexcept{
        if (x.get_alloc() == this->get_alloc()){
            move_assign(std::move(x));
        } else{
            this->assign(std::__make_move_if_noexcept_iterator(x.begin()),std::__make_move_if_noexcept_iterator(x.end()));
            x.clear();
        }
    }
    template<typename p> p* data_ptr(p* ptr) const noexcept { return ptr; }
    template<typename Ptr> typename std::pointer_traits<Ptr>::element_type* data_ptr(Ptr ptr) const{
        return empty() ? nullptr : std::__addressof(*ptr);
    }


};

template<typename T, typename Alloc> inline bool operator== (const StrongVector<T,Alloc>& x, const StrongVector<T,Alloc>& y){
    return (x.size() == y.size() && std::equal(x.begin(),x.end(), y.begin()));
}
template<typename T, typename Alloc> inline bool operator!= (const StrongVector<T,Alloc>& x, const StrongVector<T,Alloc>& y){
    return !(x.size() == y.size() && std::equal(x.begin(),x.end(), y.begin()));
}
template<typename T, typename Alloc> inline bool operator< (const StrongVector<T,Alloc>& x, const StrongVector<T,Alloc>& y){
    return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}
template<typename T, typename Alloc> inline bool operator> (const StrongVector<T,Alloc>& x, const StrongVector<T,Alloc>& y){
    return y < x;
}
template<typename T, typename Alloc> inline bool operator<= (const StrongVector<T,Alloc>& x, const StrongVector<T,Alloc>& y){
    return !(y < x);
}
template<typename T, typename Alloc> inline bool operator>= (const StrongVector<T,Alloc>& x, const StrongVector<T,Alloc>& y){
    return !(x < y);
}
template<typename T, typename Alloc> inline void swap (StrongVector<T,Alloc>& x, StrongVector<T,Alloc>& y) noexcept(noexcept(x.swap(y))){
 x.swap(y);
}


#endif //STRONGVECTOR_STRONGVECTOR_H
