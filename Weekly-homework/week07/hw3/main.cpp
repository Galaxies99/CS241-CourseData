#include "Simple_window.h"
#include "Graph.h"
#include "Binary_tree.h"
#include "TriangleBinary_tree.h"
#include "std_lib_facilities.h"
#include <iostream>

int main() {
    int levels;
    cout << "Please input levels: ";
    cin >> levels;

    Point tl(100, 100);
    Simple_window win(tl, 1100, 600, "BinaryTree");
    Binary_tree bin(levels);
    TriangleBinary_tree bin2(levels);

    bin.set_color(Color :: red);
    bin2.set_color(Color :: blue);

    win.attach(bin);
    win.attach(bin2);

    win.wait_for_button();
    return 0;
}
