#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "calc_common.h"

class TCalculator
{
    public:
        TCalculator();
        ~TCalculator();
        char* RemoveSpaces(char* str);
        bool CheckExpression(char* str);
        void ParseExpression(char* expression);
        void PrintArray();

        void CreateTree();
        void PrintTree();
        bool CalcTree();
        int CalcResult();
        int CalcNode(Node* Parent);


    protected:
    private:
        Item** array;
        int array_length;
        TTree* Tree;

        bool IsOperation(char c);
        void AddArrayItem(Item* p);
        void PrintNode(Node* Parent);

};

#endif // CALCULATOR_H
