#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int key = 25;

    int mas_int[100];

    for(int i = 0; i < 100; i++)
    {
        mas_int[i] = 1;
    }



    return a.exec();
}
