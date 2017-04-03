#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

template <class T>
ostream& operator<<(ostream& o, const vector<T>& v) {
    o << "[";
    for(auto& x : v) {
        o << x << ", ";
    }
    return o << "]";
}

template <class TFunc, class TResult, class TParam1>
void test(TResult expect, TFunc f, TParam1 p1) {
    auto got = f(p1);
    if(got != expect) {
        cerr << "failed: " << expect << " != " << got << endl;
    }else{
        std::cout<< "Test passed!"<< std::endl;
    }
}

template <class TFunc, class TResult, class TParam1, class TParam2>
void test(TResult expect, TFunc f, TParam1 p1, TParam2 p2) {
    auto got = f(p1, p2);
    if(got != expect) {
        cerr << "failed: f(" << p1 << ", " << p2 << ") = "
            << got << " != " << expect << endl;
    }else{
        std::cout<< "Test passed!"<< std::endl;
    }
}

template <class TFunc, class TResult, class TParam1, class TParam2, class TParam3, class TParam4>
void test(TResult expect, TFunc f, TParam1 p1, TParam2 p2, TParam3 p3, TParam4 p4) {
    auto got = f(p1, p2, p3, p4);
    if(got != expect) {
        cerr << "failed: f(" << p1 << ", " << p2 << ", " << p3 << ", " << p4 << ") = "
            << got << " != " << expect << endl;
    }else{
        std::cout<< "Test passed!"<< std::endl;
    }
}

int search_0(int v[], size_t size, int key) {
    for (int i = 0; i < size; ++i) {
        if (v[i] == key) {
            return i;
        }
    }

    return -1;
}

int search_1(int v[], size_t size, int key) {
    v[size] = key;

    int i = 0;
    while (v[i] != key) {   ++i; }

    if (i != size) {
        return i;
    }

    return -1;
}

int search_2(const std::vector<int>& v, int key) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == key) {
            return i;
        }
    }

    return -1;
}

int search_3(std::vector<int>& v, int key) {
    v.push_back(key);
    int i = 0;
    while (v[i] != key) {
        ++i;
    }
    v.pop_back();

    if (i != v.size()) {
        return i;
    }

    return -1;
}

int binary_search_helper
(
    const  vector<int>& v,
    size_t begin,
    size_t end,
    int key
)
{
    assert(std::is_sorted(v.begin(), v.end()));

    if (begin == end) return -1;
    if (end-begin == 1) {
        if (v[begin] == key)
            return begin;
        else
            return -1;
    }

    // [b, e) = [b, m) U [m, e)
    size_t m = (begin + end) / 2;
    assert((m-begin) + (end-m) == (end-begin));
    if (key < v[m]) {
        return binary_search_helper(v, begin, m, key);
    } else if (v[m] < key) {
        return binary_search_helper(v, m, end, key);
    } else if ( begin <= m-1 && key == v[m-1]) {
        return binary_search_helper(v, begin, m, key);
    } else {
        return m;
    }
}


int binary_search_helper_v_3
(
    const  vector<int>& v,
    size_t begin,
    size_t end,
    int key,
    size_t depth = 0
)
{
    assert(depth < 1000);
    assert(std::is_sorted(v.begin(), v.end()));
    if(begin < end)
    {
         // [b, e) = [b, m) U [m] U [m, e)
        size_t m = (begin + end) / 2;
        assert((m-begin) + (end-m) == (end-begin));
        if (key < v[m]) {
            return binary_search_helper_v_3(v, begin, m, key, depth+1);
        } else if (v[m] < key) {
            return binary_search_helper_v_3(v, m, end, key, depth+1);
        } else if ( begin <= m-1 && key == v[m-1]) {
            return binary_search_helper_v_3(v, begin, m, key, depth+1);
        } else {
            return m;
        }
    }
}

int binary_search
(
    const  vector<int>& vec,
    int x1,
    int x2,
    int key
)
{
    assert(std::is_sorted(vec.begin(), vec.end()));

    size_t b = 0;
    size_t e = vec.size();

    //if(b == e)
   //     return -1;

    while( b < e){
        //assert(b < e);
         // [b, e) = [b, m) U [m] U [m, e)
        size_t m = b + (e - b) / 2;// способ деления на два между двумя довольно большими числами
        //>>k /2^k
        // size_t m = b + (e - b)>>1;
        //assert((m-begin) + (end-m) == (end-begin));
        if (key < vec[m]) {
            e = m;
        } else if (vec[m] < key) {
            b= m+1;
        //} else if ( b <= m-1 && key == vec[m-1]) {
        //     e = m;
        } else {
            return m;
        }
    }

    return -1;
}

void test_search() {

    typedef vector<int> Array;

    auto search = search_2;

    auto key = 8;
    std::cout<< "Start testing:"<< std::endl;
    // key not exists in array
        test(-1, search, Array(), key); // degerate
        test(-1, search, Array({key-1}), key); // trivial
        test(-1, search, Array({key-1, key+1}), key); // trivial2
        test(-1, search, Array({1,2,3,4,5,7}), key); // general
        test(-1, search, Array({9,10,11,12}), key); // general
        test(-1, search, Array({4,1,2,7,10}), key); // general
    // key exists in array
        // non appliable // degerate
        test(0, search, Array({key}), key); // trivial
        test(0, search, Array({key, key+1}), key); // trivial2
        test(1, search, Array({key-1, key}), key); // trivial2
        test(8, search, Array({0,1,2,3,4,5,6,7,key}), key); // general
        test(0, search, Array({key, 9,10,11,12}), key); // general
        test(2, search, Array({4,1,key,7,10}), key); // general

        test(0, search, Array({key,1,key,7,10}), key); // general
        test(2, search, Array({2,1,key,7,key}), key); // general
     std::cout<< "Compleated testing!"<< std::endl;
}

void test_binary_search_1() {

    typedef vector<int> Array;

    auto search = binary_search_helper;

    auto key = 8;
    auto b=0;
    std::cout<< "Start testing:"<< std::endl;
    std::cout<< "key not exists in array:"<< std::endl;
    // key not exists in array
        test(-1, search, Array(), b, b, key); // degerate
        test(-1, search, Array({key-1}), b, b+1, key); // trivial
        test(-1, search, Array({key-1, key+1}), b, b+2, key); // trivial2
        test(-1, search, Array({1,2,3,4,5,7}), b, b+6, key); // general
        test(-1, search, Array({9,10,11,12}), b, b+4, key); // general
        test(-1, search, Array({0,1,3,7,10}), b, b+5, key); // general
    // key exists in array
    std::cout<< "key exists in array:"<< std::endl;
        // non appliable // degerate
        test(0, search, Array({key}), b, b+1, key); // trivial
        test(0, search, Array({key, key+1}),b, b+2, key); // trivial2
        test(1, search, Array({key-1, key}), b, b+2, key); // trivial2
        test(8, search, Array({0,1,2,3,4,5,6,7,key}), b, b+9, key); // general
        test(0, search, Array({key, 9,10,11,12}), b, b+5, key); // general
        test(4, search, Array({0,1,2,5,key,9,10}), b, b+7, key); // general

        test(4, search, Array({1,1,5,5,key,key,9,9,10,10}), b, b+8, key); // general
        test(2, search, Array({0,1,key,key,11}), b, b+5, key); // general
        test(1, search, Array({1,key,key,key,18}), b, b+5, key); // general
        test(0, search, Array({key,key,key,key,key,key,key}), b, b+7, key); // general
     std::cout<< "Compleated testing!"<< std::endl;
}

void test_binary_search_recursive() {

    typedef vector<int> Array;

    auto search = binary_search_helper;

    auto key = 8;
    auto b=0;
    std::cout<< "Start testing:"<< std::endl;
    std::cout<< "key not exists in array:"<< std::endl;
    // key not exists in array
        test(-1, search, Array(), b, b, key); // degerate
        test(-1, search, Array({key-1}), b, b+1, key); // trivial
        test(-1, search, Array({key-1, key+1}), b, b+2, key); // trivial2
        test(-1, search, Array({1,2,3,4,5,7}), b, b+6, key); // general
        test(-1, search, Array({9,10,11,12}), b, b+4, key); // general
        test(-1, search, Array({0,1,3,7,10}), b, b+5, key); // general
    // key exists in array
    std::cout<< "key exists in array:"<< std::endl;
        // non appliable // degerate
        test(0, search, Array({key}), b, b+1, key); // trivial
        test(0, search, Array({key, key+1}),b, b+2, key); // trivial2
        test(1, search, Array({key-1, key}), b, b+2, key); // trivial2
        test(8, search, Array({0,1,2,3,4,5,6,7,key}), b, b+9, key); // general
        test(0, search, Array({key, 9,10,11,12}), b, b+5, key); // general
        test(4, search, Array({0,1,2,5,key,9,10}), b, b+7, key); // general

        test(4, search, Array({1,1,5,5,key,key,9,9,10,10}), b, b+8, key); // general
        test(2, search, Array({0,1,key,key,11}), b, b+5, key); // general
        test(1, search, Array({1,key,key,key,18}), b, b+5, key); // general
        test(0, search, Array({key,key,key,key,key,key,key}), b, b+7, key); // general
     std::cout<< "Compleated testing!"<< std::endl;
}

size_t homework_binary_search(const std::vector<int> &vec, int key)
{
   assert(std::is_sorted(vec.begin(),vec.end()));

   size_t v_begin = 0;
   size_t v_end = vec.size();

   while(v_begin < v_end) {
      size_t v_mid = (v_begin +v_end)/2;
      if(key < vec[v_mid]) {
          v_end = v_mid;
      }
      else if(vec[v_mid] < key) {
          v_begin = v_mid+1;
      }
      else if(v_begin <= v_mid -1 && vec[v_mid -1]==key) {
           v_end = v_mid;
      }
      else {
        return v_mid;
      }
   }

   return -1;
}


//////////////////////////////////////////////////////////////////////////////


size_t lower_bound ( const std::vector<int> &vec, int key)
{
    size_t begin = 0;
    size_t end = vec.size();
    while(begin < end)
    {
        size_t median = begin + (end - begin)/2;
        if(vec[median]<key)
        {
            begin = median+1;
        }
        else
        {
           end = median;
        }
    }
    return end;
}

size_t lb_binary_search ( const std::vector<int> &vec, int key)
{
    size_t end = vec.size();
    size_t lb = lower_bound(vec, key);
    if((lb != end) && !(key < vec[lb]))
        return lb;

    return end;
}

template< class TIter, class T>
TIter lower_bound_iter( TIter begin, TIter end, T& key )
{
    while(begin < end)
    {
        auto median = begin + (end - begin)/2;
        if((*median)<key)
        {
            begin = median+1;
        }
        else
        {
           end = median;
        }
    }
    return end;
}

template< class TIter, class T>
TIter lb_binary_search_iter(TIter begin, TIter end, T& key )
{
    TIter lb = lower_bound_iter(begin, end, key);
    if((lb != end) && !(key < (*lb)))
        return lb;

    return end;
}

/////

size_t upper_bound ( const std::vector<int> &vec, int key)
{
    size_t begin = 0;
    size_t end = vec.size();
    while(begin < end)
    {
        size_t median = begin + (end - begin)/2;
        if(key < vec[median])
        {
            end = median;
        }
        else
        {
            begin = median+1;
        }
    }
    return end;//can be begin
}

size_t ub_binary_search ( const std::vector<int> &vec, int key)
{
    size_t begin = 0;
    size_t end = vec.size();
    size_t ub = upper_bound(vec, key);
    if(begin != end)
    {
        if(!(ub - 1 < begin))
        {
            if(!(vec[ub - 1]<key)) {
                return ub - 1;
            }
        }
    }

    return end;
}

template< class TIter, class T>
TIter upper_bound_iter( TIter begin, TIter end, T& key )
{
    while(begin < end)
    {
        auto median = begin + (end - begin)/2;
        if(key<(*median))
        {
            end = median;
        }
        else
        {
           begin = median+1;
        }
    }
    return end;
}

template< class TIter, class T>
TIter ub_binary_search_iter(TIter begin, TIter end, T& key )
{
    TIter ub = upper_bound_iter(begin, end, key);
    if((begin != end) && !(ub - 1 < begin) && !(*(ub - 1)<key))
        return ub - 1;

    return end;
}


/////

void test_binary_search_by_lower_bound() {

    typedef vector<int> Array;

    auto search = lb_binary_search;

    auto key = 8;
    std::cout<< "Start testing:"<< std::endl;
    std::cout<< "key not exists in array:"<< std::endl;
    // key not exists in array
        test(0, search, Array(), key); // degerate
        test(1, search, Array({key-1}), key); // trivial
        test(1, search, Array({key+1}), key); // trivial
        test(2, search, Array({key-1, key+1}), key); // trivial2
        test(6, search, Array({1,2,3,4,5,7}), key); // general
        test(4, search, Array({9,10,11,12}), key); // general
        test(5, search, Array({0,1,3,7,10}), key); // general
    // key exists in array
    std::cout<< "key exists in array:"<< std::endl;
        // non appliable // degerate
        test(0, search, Array({key}), key); // trivial
        test(0, search, Array({key, key+1}), key); // trivial2
        test(1, search, Array({key-1, key}), key); // trivial2
        test(8, search, Array({0,1,2,3,4,5,6,7,key}), key); // general
        test(0, search, Array({key, 9,10,11,12}), key); // general
        test(4, search, Array({0,1,2,5,key,9,10}), key); // general

        test(4, search, Array({1,1,5,5,key,key,9,9,10,10}), key); // general
        test(2, search, Array({0,1,key,key,11}), key); // general
        test(1, search, Array({1,key,key,key,18}), key); // general
        test(0, search, Array({key,key,key,key,key,key,key}), key); // general

        test(0, search, Array({key,key,key+1,key+2}), key); // general
        test(2, search, Array({key-2,key-1,key,key}), key); // general
        test(2, search, Array({1,7,key,key}), key); // general
     std::cout<< "Compleated testing!"<< std::endl;
}

void test_binary_search_by_upper_bound() {

    typedef vector<int> Array;

    auto search = ub_binary_search;

    auto key = 8;
    std::cout<< "Start testing:"<< std::endl;
    std::cout<< "key not exists in array:"<< std::endl;
    // key not exists in array
        test(0, search, Array(), key); // degerate
        test(1, search, Array({key-1}), key); // trivial
        test(1, search, Array({key+1}), key); // trivial2
        test(2, search, Array({key-1, key+1}), key); // trivial2
        test(6, search, Array({1,2,3,4,5,7}), key); // general
        test(4, search, Array({9,10,11,12}), key); // general
        test(5, search, Array({0,1,3,7,10}), key); // general
    // key exists in array
    std::cout<< "key exists in array:"<< std::endl;
        // non appliable // degerate
        test(0, search, Array({key}), key); // trivial
        test(0, search, Array({key, key+1}), key); // trivial2
        test(1, search, Array({key-1, key}), key); // trivial2
        test(8, search, Array({0,1,2,3,4,5,6,7,key}), key); // general
        test(0, search, Array({key, 9,10,11,12}), key); // general
        test(4, search, Array({0,1,2,5,key,9,10}), key); // general

        test(5, search, Array({1,1,5,5,key,key,9,9,10,10}), key); // general
        test(3, search, Array({0,1,key,key,11}), key); // general
        test(3, search, Array({1,key,key,key,18}), key); // general
        test(6, search, Array({key,key,key,key,key,key,key}), key); // general
     std::cout<< "Compleated testing!"<< std::endl;
}

void test_search_EX(){
    typedef vector<int> Array;

    auto search = [](const vector<int> & v, int key)
    {
        auto r = lb_binary_search_iter(v.begin(), v.end(), key);
        return r !=v.end() ? r-v.begin():v.end()-v.begin();//-1;
    };

    auto key = 8;
    std::cout<< "Start testing:"<< std::endl;
    std::cout<< "key not exists in array:"<< std::endl;
    // key not exists in array
        test(0, search, Array(), key); // degerate
        test(1, search, Array({key-1}), key); // trivial
        test(1, search, Array({key+1}), key); // trivial
        test(2, search, Array({key-1, key+1}), key); // trivial2
        test(6, search, Array({1,2,3,4,5,7}), key); // general
        test(4, search, Array({9,10,11,12}), key); // general
        test(5, search, Array({0,1,3,7,10}), key); // general
    // key exists in array
    std::cout<< "key exists in array:"<< std::endl;
        // non appliable // degerate
        test(0, search, Array({key}), key); // trivial
        test(0, search, Array({key, key+1}), key); // trivial2
        test(1, search, Array({key-1, key}), key); // trivial2
        test(8, search, Array({0,1,2,3,4,5,6,7,key}), key); // general
        test(0, search, Array({key, 9,10,11,12}), key); // general
        test(4, search, Array({0,1,2,5,key,9,10}), key); // general

        test(4, search, Array({1,1,5,5,key,key,9,9,10,10}), key); // general
        test(2, search, Array({0,1,key,key,11}), key); // general
        test(1, search, Array({1,key,key,key,18}), key); // general
        test(0, search, Array({key,key,key,key,key,key,key}), key); // general

        test(0, search, Array({key,key,key+1,key+2}), key); // general
        test(2, search, Array({key-2,key-1,key,key}), key); // general
        test(2, search, Array({1,7,key,key}), key); // general
     std::cout<< "Compleated testing!"<< std::endl;
}

void test_search_EX_2(){
    typedef vector<int> Array;

    auto search = [](const vector<int> & v, int key)
    {
        auto r = ub_binary_search_iter(v.begin(), v.end(), key);
        return r !=v.end() ? r-v.begin():v.end()-v.begin();//-1;
    };

    auto key = 8;
    std::cout<< "Start testing:"<< std::endl;
    std::cout<< "key not exists in array:"<< std::endl;
    // key not exists in array
        test(0, search, Array(), key); // degerate
        test(1, search, Array({key-1}), key); // trivial
        test(1, search, Array({key+1}), key); // trivial2
        test(2, search, Array({key-1, key+1}), key); // trivial2
        test(6, search, Array({1,2,3,4,5,7}), key); // general
        test(4, search, Array({9,10,11,12}), key); // general
        test(5, search, Array({0,1,3,7,10}), key); // general
    // key exists in array
    std::cout<< "key exists in array:"<< std::endl;
        // non appliable // degerate
        test(0, search, Array({key}), key); // trivial
        test(0, search, Array({key, key+1}), key); // trivial2
        test(1, search, Array({key-1, key}), key); // trivial2
        test(8, search, Array({0,1,2,3,4,5,6,7,key}), key); // general
        test(0, search, Array({key, 9,10,11,12}), key); // general
        test(4, search, Array({0,1,2,5,key,9,10}), key); // general

        test(5, search, Array({1,1,5,5,key,key,9,9,10,10}), key); // general
        test(3, search, Array({0,1,key,key,11}), key); // general
        test(3, search, Array({1,key,key,key,18}), key); // general
        test(6, search, Array({key,key,key,key,key,key,key}), key); // general
     std::cout<< "Compleated testing!"<< std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////



/*size_t find_min_element ( const std::vector<int> &vec )
{
    size_t begin = 0;
    size_t end = vec.size();
    size_t min_elem_id = begin;

    if(begin == end)
        return end;

    while(begin++ != end)
    {

        if(vec[begin] < vec[min_elem_id])
        {
           min_elem_id = begin;
        }
    }

    return min_elem_id;
}*/

template <class TIter>
TIter min_elem_iter(TIter b, TIter e) {
    auto result = b;
    while (b < e){
        // [) = [processed) [current] [unprocessed)
        // assert(result - is minimum from [processed))
        if(*b < *result){
            result = b;
        }
        ++b;
        //assert(tmp is min from [processed))
    }
    return result;
}


/*void test_min_elem_search() {

    typedef vector<int> Array;

    auto search = find_min_element;

    auto key = 2;
    std::cout<< "Start testing:"<< std::endl;
    // key not exists in array
        test(0, search, Array()); // degerate
        // non appliable // trivial
    // key exists in array
        // non appliable // degerate
        test(0, search, Array({key})); // trivial
        test(0, search, Array({key, key+1})); // trivial2
        test(0, search, Array({key-1, key})); // trivial2
        test(8, search, Array({17,8,6,23,74,85,6,11,key})); // general
        test(0, search, Array({key, 9,10,11,12})); // general
        test(2, search, Array({90,5,key,7,10})); // general

        test(2, search, Array({key,8,key,7,10})); // general
        test(4, search, Array({5,7,key,7,key}), key); // general
     std::cout<< "Compleated testing!"<< std::endl;
}*/

template <class TIter>
TIter naive_sort(TIter b, TIter e) {
    for (auto i = b; i < e ; ++i)
    {
        assert(is_sorted(b,i));
        // [sorted) U [unsorted) = [b , i) U [i , e)
        for (auto j = i+1; j < e ; ++j)
        {
            // [unsorted) = [i] U [i+1, j) U [j, e)
            assert(min_element(i, j) == 1);
            if(*j < *i)
                swap(*i, *j);

        }
        assert(is_sorted(b,i+1));
    }

}


template <class TIter>
TIter selection_sort(TIter b, TIter e) {
    for (auto i = b; i < e ; ++i)
    {
        assert(is_sorted(b,i));
        // [sorted) U [unsorted) = [b , i) U [i , e)
        swap(*i, *min_elem_iter(i, e));

    }
    return b;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TIter>
TIter my_personal_min_element_search( TIter b, TIter e )
{
    TIter min_el = b;
    while(b < e)
    {
        if( *b < *min_el )
            min_el = b;
        ++b;
    }
    return min_el;
}


template <class TIter>
TIter my_personal_selection_sort( TIter b, TIter e )
{
    for(TIter i = b; i < e ; ++i)
    {
        TIter min_elem = my_personal_min_element_search(i, e);
        //std::cout<< "Got min ["<<min_elem - b<<"]"<< std::endl;
        //if( *min_elem < *i );
            swap( *i , *min_elem);
    }
    return b;
}

template <class TIter>
TIter bubble_sort( TIter b, TIter e )
{
    if(b == e)
        return e;
    auto sorted_begin = e - 1;
    while (b < sorted_begin)
    {
        // [unsorted) U [sorted) = [b , sb) U [sb , e)
        // (sorted_begin < e)
        assert (sorted_begin < e);
        assert (is_sorted(sorted_begin, e));

        auto j = b;
        while (j  < sorted_begin)
        {
            if(*(j +1) < *j){
               std::iter_swap(j+1, j);
            }
            ++j;
        }
        /*for (auto j = b; j < sorted_begin; ++j){
            //assert(std::reverse::max_element(b, j+1) = j);// just max_element assert in case of two equal values will not pass
            if(*(j +1) < *j){
               std::iter_swap(j+1, j);
            }
            //assert(std::reverse::max_element(b, j+1) = j);
        }*/

        --sorted_begin;
        assert (is_sorted(sorted_begin, e));
    }
    return b;
}




void test_array_sort() {

    typedef vector<int> Array;
    //typedef Array::iterator iter;


    auto sort = [](const vector<int> & v)
    {
        auto u = v;
        bubble_sort(u.begin(), u.end());
        return u;
    };


    std::cout<< "Start testing:"<< std::endl;
        test(Array(), sort, Array()); // degerate
        test(Array({1, 2}), sort, Array({1, 2})); // trivial
        test(Array({1, 2}), sort, Array({2, 1})); // trivial2
        test(Array({1, 1}), sort, Array({1, 1})); // trivial2

        test(Array({1, 1, 1}), sort, Array({1, 1, 1})); // general
        test(Array({1, 2, 3}), sort, Array({1, 2, 3})); // general
        test(Array({1, 2, 3}), sort, Array({3, 2, 1})); // general
        test(Array({1, 2, 3}), sort, Array({2, 3, 1})); // general

        test(Array({0, 1, 5, 5, 6, 7, 8}), sort, Array({8, 5, 1, 7, 6, 0, 5})); // general


     std::cout<< "Compleated testing!"<< std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

/*
template <class TIter>
TIter get_ub_index( TIter b, TIter e, TIter key_id )
{
    while(b < e)
    {
        TIter  m = b + (e - b)/2;
        if(*key_id < *m)
        {
            e = m;
        }
        else
        {
            b = m + 1;
        }
    }

    return e;
}

template <class TIter>
void insert_el_in_ub_of_sorted( TIter b, TIter e, TIter n_el )
{
   TIter ub_index = get_ub_index(b, e, n_el);

   // if((begin != end) && !(ub - 1 < begin) && !(*(ub - 1)<key))
   if (b != e)
   {
       if(!(ub_index - 1 < b))
       {
           if(*(ub_index - 1) < *(n_el))
           {
                cout << "upper bound was found!" << endl;
                while( ub_index-1 < e )
                {
                   cout << "curr upper bound [" << ub_index-1-b << "][" << *(ub_index-1) << "]" << endl;
                   std::iter_swap(ub_index-1, n_el);
                   ub_index++;
                }
           }
       }
   }

}

template <class TIter>
TIter insert_sort( TIter b, TIter e )
{
    TIter pivot = b;

    while (pivot < e)
    {
        //assert(std::is_sorted(b,m));
        //[sorted)[current_max_elem][unsorted);
        if(*(pivot+1) < *pivot)
        {
            //insert m+1 in upper bound of [sorted)
            cout << "calling insert_el_in_ub_of_sorted[" << 0 << "][" << pivot-b << "][" << (pivot+1)-b << "]" << endl;
            cout << "calling insert_el_in_ub_of_sorted[" << *b << "][" << *pivot << "][" << *(pivot+1) << "]" << endl;
            insert_el_in_ub_of_sorted( b, pivot, pivot+1 );
        }
        //
        //assert(std::is_sorted(b,m));
        pivot++;
    }

    return b;
}*/

template <class TIter>
TIter real_insert_sort( TIter b, TIter e )
{
    if( b == e)
    {
       return e;
    }
    TIter pivot = b+1;
    while (pivot < e){
        if( b == e )
        {
            cout << "b == e!" << endl;
        }
        assert(std::is_sorted(b,pivot));
        //[b,pivot)[pivot][pivot + 1, e);
        auto i = pivot;
        while (b < i && *i < *(i-1)){
            assert(std::is_sorted(b,i));
            assert(std::is_sorted(i,pivot));
            std::iter_swap(i, i-1);
            --i;
            assert(std::is_sorted(b,i));
            assert(std::is_sorted(i,pivot));
        }
        //
        assert(std::is_sorted(b,pivot));
        ++pivot;
    }
    return b;
}


void test_insert_sort() {

    typedef vector<int> Array;

    auto sort = [](const vector<int> & v)
    {
        auto u = v;
        real_insert_sort(u.begin(), u.end());
        return u;
    };


    std::cout<< "Start testing:"<< std::endl;
        test(Array(), sort, Array()); // degerate
        test(Array({1, 2}), sort, Array({1, 2})); // trivial
        test(Array({1, 2}), sort, Array({2, 1})); // trivial2
        test(Array({1, 1}), sort, Array({1, 1})); // trivial2

        test(Array({1, 1, 1}), sort, Array({1, 1, 1})); // general
        test(Array({1, 2, 3}), sort, Array({1, 2, 3})); // general
        test(Array({1, 2, 3}), sort, Array({3, 2, 1})); // general
        test(Array({1, 2, 3}), sort, Array({2, 3, 1})); // general

        test(Array({0, 1, 5, 5, 6, 7, 8}), sort, Array({8, 5, 1, 7, 6, 0, 5})); // general


     std::cout<< "Compleated testing!"<< std::endl;
}


//python
/*
def merge_sort(v):
 if(len(v) > 1):
    m = len(v) // 2

    left = merge_sort(v[:m])
    right = merge_sort(v[m:])


    v = merge (left, right)
 return v
/////
def merge_sort(v):
 if(len(v) > 2):
    return v

    m = len(v) // 2
    left = merge_sort(v[:m])
    right = merge_sort(v[m:])
    return merge (left, right)

 v=[9,6,7,1,8]
 print(merge_sort(v))

*/
/*
template <class TIter>
const std::vector<int>& my_epic_merge( const std::vector<int> &vec_1, const std::vector<int> &vec_2 )
{
    std::vector<int> vec_r;
    TIter b_1 = vec_1.begin();
    TIter e_1 = vec_1.end();
    TIter b_2 = vec_2.begin();
    TIter e_2 = vec_2.end();

    while (b_1 < e_1 && b_2 < e_2 )
    {
        if(*b_1 < *b_2)
        {
            vec_r.push_back(*b_1);
            ++b_1;
        }
        else
        {
            vec_r.push_back(*b_2);
            ++b_2;
        }

    }

    if(b_1 == e_1)
    {
        while (b_2 < e_2 )
        {
            vec_r.push_back(*b_2);
            ++b_2;
        }
    }
    else if(b_2 == e_2)
    {
        while (b_1 < e_1)
        {
            vec_r.push_back(*b_1);
            ++b_1;
        }
    }

    return  vec_r;
}
*/
//continue

template <class TIter>
void merge_iter( TIter b, TIter m, TIter e, TIter buff )
{

    const auto size = e - b;
    const auto old = buff;

    TIter b_1 = b;
    TIter e_1 = m;
    TIter b_2 = m;
    TIter e_2 = e;

    while (b_1 < e_1 && b_2 < e_2 )
    {
        if(*b_1 < *b_2)
        {
            //cout << "Add 1[" << *b_1 << "]" << endl;
            //std::copy(b_1, ++b_1, buff);
            *buff = *b_1++;
        }
        else
        {
            //cout << "Add 2[" << *b_2 << "]" << endl;
            //std::copy(b_2, ++b_2, buff);
            *buff = *b_2++;
        }
        ++buff;

    }



    /*
     while (b_1 < e_1 && b_2 < e_2){
        *buff++ = *b_1 < *b_2 ? *b_1++ : *b_2++;
     }
    */


    /*if(b_1 == e_1)
    {
        while (b_2 < e_2 )
        {
            //std::iter_swap(b_2, buff);
            cout << "Add 2[" << *b_2 << "]" << endl;
            std::copy(b_2, ++b_2, buff);
            ++buff;
            //++b_2;
        }
    }
    else if(b_2 == e_2)
    {
        while (b_1 < e_1)
        {
            //std::iter_swap(b_1, buff);
            cout << "Add 1[" << *b_1 << "]" << endl;
            std::copy(b_1, ++b_1, buff);
            ++buff;
            //++b_1;
        }
    }*/

    buff = copy(b_1, e_1, buff);
    buff = copy(b_2, e_2, buff);//if b_1 ==e_1 || b_2 == e_2  copy will not copy anything
    assert(buff-old == size);

}//O(N)


template <class TIter>
void merge_sort_outer(TIter b, TIter e, TIter buff){
    auto size = e - b;
    /*
    if(size>1024)
    {
       std::copy(b, e, buff);
       insert_sort(buff, buff+size);
    } else {
     */
    if(size > 1) {
        auto m = b + size/2;
        merge_sort_outer(b, m, buff);
        merge_sort_outer(m, e, buff+(size)/2);
        std::copy(buff, buff+size, b);
        merge_iter(b, m, e, buff);
    }
    else
    {
        std::copy(b, e, buff);
    }
}

template <class TIter>
void merge_sort_adapter(TIter b, TIter e){
    std::vector<int> buff(e - b);//typename std::iterator_traits<TIter>::value_type
    merge_sort_outer(b, e, buff.begin());
    copy(buff.begin(), buff.end(), b);
}

/*template <class TIter>
void merge_sort_whiled_outer(TIter b, TIter e, TIter buff){
    auto size = e - b;
    auto starter = b;
    std::copy(b, e, buff);
    auto step = e;
    int step_count=1;

    while(step>2)
    {
       step = (b + (step - b))/2;
       step_count++;
    }

    while(step_count > 0)
    {
        while(starter < e)
        {
            auto m = (starter + (step - starter))/2;
            std::copy(buff, buff+step, starter);
            merge_iter(starter, m, starter+step, buff);
            starter=starter+step;
        }
        step_count--;
    }
}

template <class TIter>
void merge_sort_whiled_adapter(TIter b, TIter e){
    std::vector<int> buff(e - b);//typename std::iterator_traits<TIter>::value_type
    merge_sort_whiled_outer(b, e, buff.begin());
    copy(buff.begin(), buff.end(), b);
}*/

void test_merge_sort() {

    typedef vector<int> Array;

    auto sort = [](const vector<int> & v)
    {
        auto u = v;
        merge_sort_adapter(u.begin(), u.end());
        return u;
    };


    std::cout<< "Start testing:"<< std::endl;
        test(Array(), sort, Array()); // degerate
        test(Array({1, 2}), sort, Array({1, 2})); // trivial
        test(Array({1, 2}), sort, Array({2, 1})); // trivial2
        test(Array({1, 1}), sort, Array({1, 1})); // trivial2

        test(Array({1, 1, 1}), sort, Array({1, 1, 1})); // general
        test(Array({1, 2, 3}), sort, Array({1, 2, 3})); // general
        test(Array({1, 2, 3}), sort, Array({3, 2, 1})); // general
        test(Array({1, 2, 3}), sort, Array({2, 3, 1})); // general

        test(Array({0, 1, 5, 5, 6, 7, 8}), sort, Array({8, 5, 1, 7, 6, 0, 5})); // general


     std::cout<< "Compleated testing!"<< std::endl;
}


/*void test_alter_merge(){
    typedef vector<int> Array;
    std::cout<< "Start testing:"<< std::endl;
    auto sort_fun = my_epic_merge;
    test(Array({1,2,3,3,4,4,5,5,6,6,7,8}), sort_fun, Array({1,2,3,4,5,6}), Array({3,4,5,6,7,8})); // general
    std::cout<< "Test complete!"<< std::endl;
}*/

//template< class Iter, class T>
//auto search  = bs_by_lb <Array::iterator, int>;


/////////////////////////////////////////////////////////////////////////////////////

/*template <class TIter>
void quick_sort(TIter b, TIter e){
    if(e-b < 2)
    {
        return;
    }
    auto p = select_pivot(b, e);
     p = partition (b, p ,e);
    //assert (max (b, p) <= *p && p < min (p+1, e));
    quick_sort(b, p);
    quick_sort(p+1, e);
}*/

template <class TIter>
TIter pivot_strategy(TIter b, TIter e){
    assert(b<e);
    auto m = b + (e-b)/2;
    auto last = e -1;
    /*if (*b < * m){
         if (*m < *last)
             return m;
         else
             return last;
    }
    else
    {
      return b;
    }*/
    //not sure
    if(*m< *b) swap(b, m);
    if(*last< *m) swap(last, m);
    if(*m< *b) swap(b, m);
    return m;
}



template <class TIter>
TIter my_partition(TIter b, TIter k, TIter e){
    /*int key = *k;

    while(k < e)
    {
        if(k-1 >= b || k+1 < e)
        {
            if(*k-1 < key && key < *k+1)
            {
                return k;
            }
        }
      k++;
    }
    return k;*/
    assert (b < e);
    auto pivot  = *k;
    swap(*(e-1), *k);//adding pivot to the end of it's related group
    auto ub = b;
    auto ue = e-1;
    // [b, ub) [ub, ue) [ue, e)
    // [ <p  ) [      ) [ p<= )
    while(ub < ue)
    {
       if(*ub < pivot){
        ++ub;
       } else {
        --ue;
        swap (*ub, *ue);
       }
    }
    std::swap(*ub, *(e-1));
    return ub;
}

template <class TIter>
TIter my_partition_2(TIter b, TIter k, TIter e){
    assert (b < e);
    auto pivot  = *k;
    swap(*(e-1), *k);//adding pivot to the end of it's related group
    //auto b1 = b;
    //auto e1 = b;
    auto b2 = b;//e1;
    //auto e2 = b;
    auto ub = b;//e2;
    auto ue = e;
    // [b1, e1) [b2, e2) [ub, ue)
    // [ <p   ) [ p<=  ) [ unpr )
    while(ub < ue-1)
    {
       if(*ub < pivot){
        swap (*b2, *ub);
        ++b2;
       }
       ++ub;
    }
    std::swap(*b2, *(ue-1));
    return b2;
}

template <class TIter>
void quick_sort_simplify(TIter b, TIter e){
    if(e-b > 1)
    {
        auto p = my_partition_2 (b, b ,e);
        //assert (max (b, p) <= *p && p < min (p+1, e));
        quick_sort_simplify(b, p);
        quick_sort_simplify(p+1, e);
    }
}

void test_quick_sort() {

    typedef vector<int> Array;

    auto sort = [](const vector<int> & v)
    {
        auto u = v;
        quick_sort_simplify(u.begin(), u.end());
        return u;
    };


    std::cout<< "Start testing:"<< std::endl;
        test(Array(), sort, Array()); // degerate
        test(Array({1, 2}), sort, Array({1, 2})); // trivial
        test(Array({1, 2}), sort, Array({2, 1})); // trivial2
        test(Array({1, 1}), sort, Array({1, 1})); // trivial2

        test(Array({1, 1, 1}), sort, Array({1, 1, 1})); // general
        test(Array({1, 2, 3}), sort, Array({1, 2, 3})); // general
        test(Array({1, 2, 3}), sort, Array({3, 2, 1})); // general
        test(Array({1, 2, 3}), sort, Array({2, 3, 1})); // general

        test(Array({0, 1, 5, 5, 6, 7, 8}), sort, Array({8, 5, 1, 7, 6, 0, 5})); // general


     std::cout<< "Compleated testing!"<< std::endl;
}

/*int main(int argc, char const *argv[])
{
    test_search();
    return 0;
}*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    test_quick_sort();
    return a.exec();
}
