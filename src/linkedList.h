#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "struct.h"

typedef struct listNode{
    Users users;
    struct listNode* next;
};