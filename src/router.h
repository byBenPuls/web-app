#ifndef ROUTER_H
#define ROUTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*Handler)(char *, size_t);

typedef struct Route
{
    char *path;
    Handler handler;
    struct Route *next;
} Route;

typedef struct Router
{
    Route *head;
} Router;

Router *create_router();
void add_route(Router *router, const char *path, Handler handler);
void handle_request(Router *router, const char *path, char *response, size_t response_size);
void free_router(Router *router);

#endif // ROUTER_H