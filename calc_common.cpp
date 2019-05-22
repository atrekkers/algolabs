#include <string.h>
#include <iostream>
#include <cstdlib>
#include "calc_common.h"

using namespace std;

TStack::TStack()
{
    Top = 0;
}

bool TStack::Empty()
{
    return (Top == 0);
}

Item* TStack::GetTopElement()
{
    return Body[Top - 1];
}

int TStack::Priority(Item* x)
{
    if (x->Data == '^') return 4;
    if ((x->Data == '*')||(x->Data == '/')) return 3;
    if ((x->Data == '+')||(x->Data == '-')) return 2;
    if (x->Data == '(') return 1;
    if (x->Data == ')') return 0;
    return 5;
}

int TStack::TopPriority()
{
    return Priority(Body[Top - 1]);
}

void TStack::Add(Item* x)
{
    Top++;

    if (Top == 1)
    {
        Body = (Item**) malloc(sizeof(Item*));
    }

    else
    {
        Body = (Item**) realloc(Body, Top*sizeof(Item*));
    }

    Body[Top - 1] = x;
}

Item* TStack::Remove()
{
    Top--;
    if (Top != 0)
    {
        Body = (Item**) realloc(Body, Top*sizeof(Item*));
        return Body[Top - 1];
    }
    else
    {
        return NULL;
    }
}

void TStack::Print()
{
    for (int i = 0; i < Top; i++)
    {
        cout << Body[i]->Data.toStdString().c_str() << endl;
    }
}

//stack realization ended

//TTree realization started

Node::Node()
{
    left = NULL;
    right = NULL;
    parent = NULL;
    calc_result = 0;
}

TTree::TTree()
{
    NodesCount = 0;
    Nodes = NULL;
}

TTree::~TTree()
{
    if (Nodes)
    {
         for (int i = 0; i < NodesCount; i++)
         {
             delete &Nodes[i];
         }

         free(Nodes);

    }
}

Node* TTree::Add(Node* Parent, Item* Data)
{
    if (Parent == NULL)
    {
        Parent = (Node*) new Node;
        Parent->Data = Data->Data;
        Parent->Item_type = Data->Item_type;

        AddNodesItem(Parent);

        return Parent;
    }

    if (Parent->Item_type == NUMBER)
    {
        Node* OperNode = FreeOperNode();
        if (OperNode)
        {
            OperNode->left = Add(OperNode->left, Data);
        }
        return Parent;
    }


    if(!Parent->right)   //запись вправо
    {
        Parent->right = Add(Parent->right, Data);
        Parent->right->parent = Parent;
    }
    else
    {
        if (!(Parent->left) && (Parent->right->Item_type == ACTION))//если записано не число, записываем число сюда
        {
            Parent->right = Add(Parent->right, Data);
            Parent->right->parent = Parent;
        }
        else   //число
        {
            Parent->left = Add(Parent->left, Data);   //иначе записываем влево
            Parent->left->parent = Parent;
        }
    }

    return Parent;
}

void TTree::AddNodesItem(Node* p)
{
    NodesCount++;

    if (!Nodes)
    {
        Nodes = (Node**) malloc(sizeof(Node*));
    }

    else
    {
        Nodes = (Node**) realloc(Nodes, NodesCount*sizeof(Node*));
    }

    Nodes[NodesCount - 1] = p;
}

Node* TTree::FirstNode()
{
    if (Nodes)
    {
        return Nodes[0];
    }

    return NULL;
}

Node* TTree::FreeOperNode()
{
    if (Nodes)
    {
        for (int i = 0; i < NodesCount; i++)
        {
            if (Nodes[i]->Item_type == ACTION)
            {
                if (!Nodes[i]->left)
                {
                    return Nodes[i];
                }
            }
        }
    }

    return NULL;
}
