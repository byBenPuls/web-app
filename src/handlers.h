#ifndef HANDLERS_H
#define HANDLERS_H

#include <stdio.h>

void hello_handler(char *response, size_t response_size);
void goodbye_handler(char *response, size_t response_size);
void main_handler(char *response, size_t response_size);

#endif // HANDLERS_H