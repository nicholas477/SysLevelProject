// Our "main" header, include this in every c file

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <ncurses.h>

typedef enum LibraryState
{
    Add,
    Delete,
    Checkout,
    Return,
    Status,
    Query,
    List
}