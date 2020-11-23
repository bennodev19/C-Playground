#include <iostream>
#include <vector>
#include <string>

using namespace ::std;

    // https://www.geeksforgeeks.org/vector-in-cpp-stl/
    // https://www.bitdegree.org/learn/c-plus-plus-vector
    // https://www.edureka.co/blog/vectors-in-cpp/

int main()
{
    vector<string> myList;

    myList.push_back("hans");
    myList.push_back("frank");
    myList.push_back("dieter");

    for (int i = 0; i < myList.size(); i++)
    {
        cout << myList[i] << endl;
    }

    return 0;
}