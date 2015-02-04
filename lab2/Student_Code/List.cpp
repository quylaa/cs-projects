// Written by Aleks Christensen

#include "List.h"

List::List(void) : LinkedListInterface(void)
{
    List<T>() : listSize(INIT_SIZE), list(new T[INIT_SIZE]), numItems(0)
}
List::~List(void){}

void insertHead(T value)
{
    for (size_t i = 0; i < sizeof(list); i++) {

