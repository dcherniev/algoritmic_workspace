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

void test_binary_search() {

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


/*int main(int argc, char const *argv[])
{
    test_search();
    return 0;
}*/


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    test_binary_search();
    return a.exec();
}
