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
        int getLessThanPrevious();
        int read(const char *fname);
        void print(int max_print);
        void del();

        void bubbleSort();
        void minSort();
        void insertSort();
        void mergeSort();
        void quickSort();
};
void printList(list_node *head);
