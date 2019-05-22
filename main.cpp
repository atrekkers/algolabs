#include <QCoreApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QString>
#include <iostream>

#include "calc_common.h"
#include "calculator.h"

QTextStream cout(stdout);
QTextStream cin(stdin);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QString s;

    char s[255];

    cout << "Enter expression: " << endl;
    //s = cin.readLine();
    gets(s);

    TCalculator* calc = new TCalculator;

    strcpy(s, calc->RemoveSpaces(s));
    bool ResCEx = calc->CheckExpression(s);

    if (ResCEx == true)
    {
        calc->ParseExpression(s);
        cout << "parse_end" << endl;
        calc->PrintArray();
        cout << endl;
        calc->CreateTree();
        calc->PrintTree();
        cout << endl;
        calc->CalcTree();
        cout << "result = " << calc->CalcResult() << endl;
        //cout << "create_tree_end" << endl;


        //(2^3^5^(4-2*5+12/2))-32*(-1)-(-2)+1 должно быть равно 51, а не 35
    }
    else
    {
        cout << "Expression is incorrect" << endl;
    }

    delete calc;

    cout << "end" << endl;

    return a.exec();
}
