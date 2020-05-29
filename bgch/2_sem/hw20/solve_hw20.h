#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


int number_of_max_elems(list *head); //1
int number_of_elems_greater_than_previous(list *head); //2
int number_of_local_max(list *head); //3
int maxlen_between_local_max(list *head); //4
int maxlen_up_seqence(list *head); //5
int number_of_const_seqence(list *head); //6
int maxlen_between_const_seqence(list *head); //7
list *list_without_elems_not_greater_then_next(list *head); //8
list *list_without_elems_not_greater_then_neighbours(list *head); //9
list *list_without_down_sequences(list *head); //10
