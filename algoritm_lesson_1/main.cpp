#include <QCoreApplication>
#include <iostream>

using namespace std;

//ddolzhenko/training_algs_2017

/*int SearchForMin( int vec[], size_t size )
{
    // vec[-1] ~ *(vec + -1 (sizeof(type)) ~ *(vec -4)
    // (-1)vec = 1234;

    int key_index = 0;
    int current_min = mas_int[0];

    for(int i = 1; i < size; i++)
    {
       if(mas_int[i] > current_min)
       {
           current_min = mas_int[i];
           key_index = i;
       }
    }

    return key_index;
}*/



int SearchForMin( const std::vector<int> &vec )
{
    int key_index = 0;
    int current_min = vec[0];

    for(int i = 1; i < vec.size(); i++)
    {
       if(vec[i] < current_min)
       {
           current_min = vec[i];
           key_index = i;
       }
    }

    return key_index;
}



template <class TResult, class TFunc , class Tparam1>
void test( TResult expect,  TFunc f, Tparam1 p1)
{
    auto got = f(p1);
    if(got !=expect)
    {
        cerr << "failed: " << expect << " != " << got << endl;
    }

}

template <class TFunc, class TResult, class Tparam1, class Tparam2>

void test( TFunc expect, TResult f, Tparam1 p1, Tparam2 p2)
{
    auto got = f(p1, p2);
    if(got !=expect)
    {
        cerr << "failed: " << expect << " != " << got << endl;
    }
    else
    {
        cout << "great succsess!"  << endl;
    }

}


int SearchForKey( const std::vector<int> &vec, int key )
{
    int key_index = -1;

    for(int i = 0; i < vec.size(); i++)
    {
       if(vec[i] == key)
       {
           key_index = i;
           break;
       }
    }

    return key_index;
}

void test_search()
{
    typedef vector<int> my_array;

    auto search = SearchForKey;
    auto key =8;

    cout << "key not exist in array" << endl;
    //key not exist in array
        //degerate
        test(-1, search, my_array(), key);
        //trivial
        test(-1, search, my_array({key-1}), key);
        //trivial-2
        test(-1, search, my_array({key-1, key+1}), key);
        //general(few)
        test(-1, search, my_array({0, 1, 2, 3, 4, 5, 6, 7}), key);
        test(-1, search, my_array({9, 10, 11, 12}), key);
        test(-1, search, my_array({4, 1, 2, 7, 10}), key);

    cout << "key exist in array" << endl;
    //key exist in array
        //degerate
        ///! not appliable
        //trivial
        test(0, search, my_array({key}), key);
        //trivial-2
        test(1, search, my_array({key-1, key}), key);
        test(0, search, my_array({key, key+1}), key);
        //general(few)
        test(8, search, my_array({0, 1, 2, 3, 4, 5, 6, 7, key}), key);
        test(0, search, my_array({key, 9, 10, 11, 12}), key);
        test(2, search, my_array({4, 1, key, 2, 7, 10}), key);
        test(0, search, my_array({key, 1, key, 7, 10}), key);
        test(2, search, my_array({2, 1, key, 2, 7, key}), key);
    cout << "key exist in array" << endl;





    //test(8, SearchForKey, my_array({1, 2, 3, 4, 5, 6, 7, 8, 9}), 8);
}


///Book: Grady Buch "объектно ориентированный анализ..."

int BinarySearchHelper(const vector<int>& vec, size_t b, size_t e, int key)
{
    assert(std::is_sorted(v.begin(), vend()));//Я утверждаю что...

    // [0, m) ,[m, s) (m-0) + (s-m) = s

    //size_t b = 0;
    //size_t e = vec.size();

    if(b == e) return -1;
    if(e - b == 1)
        if (vec[begin] ==  key)
            return begin;
        else
            return -1;

    // [0, s)  = [0, m) U [m, s)
    size_t m = (b - e) / 2;
    assert((m-b)+(e-m)==(e-b));

    if(key < vec[m]){
        return BinarySearch(vec, b, m, key);
    }
    else if(vec[m] < key)//key > vec[m] )
    {
        return BinarySearch(vec, m, e, key);
    }
    else
    {
        return m;
    }
    //HW: find two mistakes
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //int key = 25;
    int size = 100;

    std::vector<int> mas_int;

    for(int i = 0; i < size; i++)
    {
        mas_int.push_back(rand() % 10000);
        std::cout<<"mas_int["<<i<<"] ="<< mas_int[i]<<"\n";
    }

    int key_index = SearchForMin( mas_int );
    std::cout<<"key_index =" << key_index<<"\n";

    test_search();

    return a.exec();
}
