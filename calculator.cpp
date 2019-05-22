#include <ctype.h>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "calculator.h"

TCalculator::TCalculator()
{
    array = NULL;
    array_length = 0;
    Tree = NULL;
}

TCalculator::~TCalculator()
{
    if (array)
    {
         for (int i = 0; i < array_length; i++)
         {
             delete &array[i];
         }

         free(array);

    }

    if (Tree)
    {
        delete Tree;
    }

}

char* TCalculator::RemoveSpaces(char* str)
{
    char* res = str;
    int m = strlen(res);
    int i = 0;
    int j = 0;

    while(*res == ' ')
    {
        res++;
    }

    for (i = 0; i < m; i++)
    {
        if (res[i] == ' ')
        {
            for (j = i; j < strlen(res); j++)
            {
                res[j] = res[j + 1];
                i--;
            }
        }
    }

    if (res[strlen(res)-1] == ' ')
    {
        res[strlen(res)-1] = '\0';
    }

    return(res);
}

bool TCalculator::IsOperation(char c)
{
    return (
            (c == '+') ||
            (c == '-') ||
            (c == '*') ||
            (c == '/') ||
            (c == '(') ||
            (c == ')') ||
            (c == '^')
       );
}

bool TCalculator::CheckExpression(char* str)
{
    char* r = str;

    while(*r != '\0')
    {
        if (!(isdigit(*r) || IsOperation(*r)))
        {
            return false;
        }

        r++;
    }

    return true;
}

void TCalculator::AddArrayItem(Item* p)
{
    array_length++;

    if (!array)
    {
        array = (Item**) malloc(sizeof(Item*));
    }

    else
    {
        array = (Item**) realloc(array, array_length*sizeof(Item*));
    }

    array[array_length - 1] = p;
}

void TCalculator::PrintArray()
{
    for (int i = 0; i < array_length; i++)
    {
        std::cout << array[i]->Data.toStdString().c_str();
    }
}

void TCalculator::ParseExpression(char* expression)
{
    char* r = expression;
    char* t;
    char number[128];
    int itcount = 0;
    Item* p;
    TStack* s = (TStack*) new TStack;

    while(*r != '\0')
    {
        if (isdigit(*r))
        {
            if (number[0] == '-')
            {
                strncat(number, r, 1);
            }
            else
            {
                strncpy(number, r, 1);
            }

            t = r;

            while (isdigit(*(++t)))
            {
                strncat(number, t, 1);
            }

            r = t - 1;

            p = (Item*) new Item;

            p->Data = number;
            p->Item_type = NUMBER;

            AddArrayItem(p);

            memset(number, 0, sizeof(number));
        }
        else
        {
            if (*r == '-')
            {
                if ((itcount == 0) || (!isdigit(*(r-1)) && (*(r+1) != '\0') && isdigit(*(r+1))))
                {
                    strncpy(number, r, 1);
                    r++;
                    itcount++;
                    continue;
                }
            }
            if (IsOperation(*r))
            {
                p = (Item*) new Item;

                p->Data = *r;
                p->Item_type = ACTION;


                if (s->Empty() || (*r == '('))
                {
                    s->Add(p);
                }
                else
                {
                    if (*r == ')')
                    {
                        while (!(s->Empty()) && (s->GetTopElement()->Data != '('))
                        {
                            AddArrayItem(s->GetTopElement());
                            s->Remove();
                        }

                        s->Remove();
                    }
                    else
                    {
                        if ((s->Priority(p) > s->TopPriority()) || (s->Priority(p) == 4))
                        {
                             s->Add(p);
                        }
                        else
                        {
                            while(!(s->Empty()) && (s->Priority(p) <= s->TopPriority()))
                            {
                                AddArrayItem(s->GetTopElement());
                                s->Remove();
                            }

                            s->Add(p);
                        }
                    }
                }
            }
        }

        r++;
        itcount++;
    }

    while (!(s->Empty()))
    {
        AddArrayItem(s->GetTopElement());
        s->Remove();
    }

    delete s;
}

void TCalculator::CreateTree()
{
    Node* n = NULL;

    if (!Tree)
    {
        Tree = (TTree*) new TTree;
    }

    for (int i = array_length - 1; i >= 0; i--)
    {
        n = Tree->Add(n, array[i]);
    }
}

void TCalculator::PrintNode(Node* Parent)
{
    if (!Parent)
    {
        return;
    }

    if (Parent->left)
    {
        PrintNode(Parent->left);
    }

    std::cout << Parent->Data.toStdString().c_str() << std::endl;

    if (Parent->right)
    {
        PrintNode(Parent->right);
    }
}

void TCalculator::PrintTree()
{
    PrintNode(Tree->FirstNode());
}

int TCalculator::CalcNode(Node* Parent)
{
    if(Parent->left)
    {
        Parent->calc_result = CalcNode(Parent->left);
    }
    /*else
    {
       return atoi(Parent->Data.toStdString().c_str());
    }*/

    if(Parent->right)
    {
        switch(Parent->Data.toStdString().c_str()[0])
        {
            case '+': Parent->calc_result += CalcNode(Parent->right); break;
            case '-': Parent->calc_result -= CalcNode(Parent->right); break;
            case '*': Parent->calc_result *= CalcNode(Parent->right); break;
            case '/': Parent->calc_result /= CalcNode(Parent->right); break;
            case '^': Parent->calc_result = pow(Parent->calc_result, CalcNode(Parent->right)); break;
        }
    }

    if (Parent->Item_type == NUMBER)
    {
        Parent->calc_result = atoi(Parent->Data.toStdString().c_str());
    }

    return Parent->calc_result;
}

bool TCalculator::CalcTree()
{
    Node* TempFN = Tree->FirstNode();

    if (!TempFN)
    {
        return false;
    }


    CalcNode(TempFN);

    return true;
}

int TCalculator::CalcResult()
{
    return Tree->FirstNode()->calc_result;
}
