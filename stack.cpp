#include "stack.h"

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
        return nullptr;
    }
}

void TStack::Print()
{
    for (int i = 0; i < Top; i++)
    {
        cout << Body[i]->Data.toStdString().c_str() << endl;
    }
}
