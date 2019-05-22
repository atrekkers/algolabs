#ifndef STACK_H
#define STACK_H

#include "calc_common.h"

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


#endif // STACK_H
