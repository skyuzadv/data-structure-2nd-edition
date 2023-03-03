#include <iostream>

#include "list_seq.hpp"

int main(int argc, char** argv) {
    List_seq<int> la, lb, lc;
    la.push_back(1);
    la.push_back(3);
    la.push_back(5);
    la.push_back(7);
    la.push_back(11);
    la.TraverseList();

    lb.push_back(2);
    lb.push_back(4);
    lb.push_back(7);
    lb.push_back(8);
    lb.push_back(10);
    lb.TraverseList();

    la.MergeList(lb, lc);
    lc.TraverseList();
    return 0;
}