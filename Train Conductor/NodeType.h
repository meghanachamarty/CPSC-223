/* Meghana Chamarty 
 * NodeType.h
 * CPSC223
 * 4/4/2023
 * Small struct that is part of a Linked List class
 *
 */

#include "Station.h"
using namespace std;

#ifndef NODETYPE
#define NODETYPE

struct NodeType
{
    Station info;
    NodeType *next;
};

#endif
