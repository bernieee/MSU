#include "student.h"
#include "list_node.h"
#include <time.h>

class list
{
    private:
        list_node *head = nullptr;

    public:
        list() = default;

        int getLength();
        list_node *getElement(int j);
        int read(const char *fname);
        void print(int max_print);
        void del();

        void cycle(int k);// to the right 1
        int move(int n, int k, int j, int steps);// 1
        void removeElemsGreaterThanAnyOfKPrevious(int k);// 2
        void removeElemsGreaterThanAnyOfKNext(int k);// 3
        void removeLocalMax(int k);// k on the right and on the left; 4
        void removeConstSeq(int k);// not strictly; len not less than k; 5
        void removeDownSeq(int k);// not strictly; len not less than k; 6
        void removeSeqBetweenConstSeq(int k);// len not less than k; 7
        void removeSeqBetweenUpSeq(int k);// not strictly; len not less than k; 8
};

//void delList(list *head);
