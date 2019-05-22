#ifndef CALC_COMMON_H
#define CALC_COMMON_H

#include <QString>
#include <stdlib.h>

enum Token_type
{
    NUMBER,
    ACTION

};

class Item
    {
        public:
            QString Data;
            Token_type Item_type;

    };

class Node:public Item
    {
        public:
            Node();
            Node* left;
            Node* right;
            Node* parent;
            int calc_result;
    };


class TTree
{
public:
    TTree();
    ~TTree();
    Node* Add(Node* Parent, Item* Data);
    Node* FirstNode();
private:
    Node** Nodes;
    int NodesCount;
    void AddNodesItem(Node* p);
    Node* FreeOperNode();
};

class TStack
    {
        public:

            TStack();
            bool Empty();
            Item* GetTopElement();
            int TopPriority();
            int Priority(Item* x);
            void Add(Item* x);
            Item* Remove();

            void Print();

        protected:
        private:
            int Top;
            Item** Body;


    };



#endif // CALC_COMMON_H
