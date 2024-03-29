#include <iostream>
#include <cstdlib> 
#include "LinkedList.hpp"

using namespace std;

template<typename T> struct Test
{
    T a, b, c;

    Test() {}
    Test(const T a, const T b, const T c) : a(a), b(b), c(c) {}
};

template<typename T> ostream& operator<<(ostream& out, const Test<T>& t) {
    return out << "{ A:" << t.a << ", B:" << t.b << ", C:" << t.c << " }";
}

List1i generateRandomList(const int size) {
    List1i result;
    srand((unsigned) time(NULL));
    
    for (int i = 0; i < size; i++) {
        result += rand();
    }

    return result;
}

int main() {

    LinkedList<int> l = generateRandomList(26000);

    cout << l << endl << endl;

    l.sort([](int a, int b){return a < b;});

    cout << l << endl << endl;

    return 0;
}
