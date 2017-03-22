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
    TIter lb = lower_bound(begin, end, key);
    if((lb != end) && !(key < (*lb)))
        return lb;

    return end;
}

size_t ub_binary_search ( const std::vector<int> &vec, int key)
{
    size_t end = vec.size();
    size_t ub = upper_bound(vec, key);
    if((ub != end) && !(vec[ub]<key))
        return ub;

    return end;
}

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

        test(4, search, Array({1,1,5,5,key,key,9,9,10,10}), key); // general
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


////////////////////////////////////////////////////////////////////////////////////////////////


//template< class Iter, class T>
//auto search  = bs_by_lb <Array::iterator, int>;

/*int main(int argc, char const *argv[])
{
    test_search();
    return 0;
}*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    test_binary_search_by_upper_bound();
    return a.exec();
}
