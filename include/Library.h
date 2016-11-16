// Our "main" header, include this in every c file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <ncurses.h>

typedef enum
{
    Add,
    Delete,
    Checkout,
    Return,
    Status,
    Query,
    List
} LibraryState;
