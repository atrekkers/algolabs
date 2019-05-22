#ifndef TREE_H
#define TREE_H

#include "calc_common.h"

class TTree
{
public:
    TTree();
    ~TTree();
    //Node* Top;
    Node* Add(Node* Parent, Item* Data);
    Node* FirstNode();
private:
    Node** Nodes;
    int NodesCount;
    bool IsRight;
    void AddNodesItem(Node* p);
};


#endif // TREE_H
