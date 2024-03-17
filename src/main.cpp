#include <iostream>
#include "LinkedList.hpp"

using namespace std;

/* TEST FILE */

int main() {


    LinkedList<int> ll;

    ll.push(5);
    ll.push(1);
    ll.push(10);

    cout << ll << endl;

    // ll += 104;

    cout << ll << endl;

    LinkedList<int> r;

    r.push(5);
    r.push(1);

    // ll *= 100;

    ll.push_copy(ll);

    r[0] = 12345;
    

    cout << ll << endl;
    cout << ll.size() << endl;


    LinkedList<LinkedList<int>> k;

    k.push(ll);
    k.push(r);

    cout << k << endl;
    cout << k.size() << endl;

    LinkedList<int> c(ll);
    cout << c << endl;
    cout << c.size() << endl;

    c.push_copy(r);
    cout << c << endl;
    cout << c.size() << endl;


    // LinkedList<int> p(ll);
    // cout << ll.beginNode() << endl;
    // cout << p.beginNode() << endl;

    // cout << ll << endl;
    // cout << p << endl;
    // cout << p.endElement() << endl;

    return 0;
}
