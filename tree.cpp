#include "tree.h"

TTree::TTree()
{
    NodesCount = 0;
    Nodes = nullptr;
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
    if (Parent == nullptr)
    {
        Parent = (Node*) new Node;
        Parent->Data = Data->Data;
        Parent->Item_type = Data->Item_type;

        AddNodesItem(Parent);

        return Parent;
    }

    if (Parent->Item_type == NUMBER)
    {
        return Parent;
    }


    if(!Parent->right)   //запись вправо
    {
        Parent->right = Add(Parent->right, Data);
        Parent->right->parent = Parent;
    }
    else
    {
        if (Parent->right->Item_type == ACTION)//если записано не число, записываем число сюда
        {
            Parent->right = Add(Parent->right, Data);
            Parent->right->parent = Parent;
        }
        else   //число
        {
            /*if (Parent->left && (Parent->left->Item_type == NUMBER))
            {
                Parent->parent->left = Add(Parent->parent->left, Data);
                Parent->parent->left->parent = Parent->parent;
            }
            else*/
            {
                Parent->left = Add(Parent->left, Data);   //иначе записываем влево
                Parent->left->parent = Parent;
            }
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

    return nullptr;
}
