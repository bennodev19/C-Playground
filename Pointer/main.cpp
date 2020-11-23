#include <iostream>
#include <string>

using namespace ::std;

// https://www.geeksforgeeks.org/vector-in-cpp-stl/
// https://www.bitdegree.org/learn/c-plus-plus-vector
// https://www.edureka.co/blog/vectors-in-cpp/

int main()
{
    int i = 5;
    int *pi, pj;
    char *pc, pd;
    int a = 0;
    pi = &a;
    pj = 0;
    pd = '0';

    pi = i;
    pi = *i;
    *pi = i;
    *pi = &i;
    pi = pj;
    pc = &pd;
    pi = pc;
    pd = *pi;
    *pi = i * *pc;
    pi = 0;

    return 0;
}