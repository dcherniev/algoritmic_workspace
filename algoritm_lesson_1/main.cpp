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

}

void test_search()
{
    typedef vector<int> my_array;
    test(8, SearchForKey, my_array(1, 2, 3, 4, 5, 6, 7, 8, 9), 8);
}

int SearchForKey( const std::vector<int> &vec, int key )
{
    int key_index = -1;

    for(int i = 1; i < vec.size(); i++)
    {
       if(vec[i] == key)
       {
           key_index = i;
       }
    }

    return key_index;
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
