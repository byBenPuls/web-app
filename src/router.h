#ifndef ROUTER_H
#define ROUTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"

typedef Response (*Handler)(Request *request);

typedef struct Route
{
    char *path;
    char *method;
    Handler handler;
    struct Route *next;
} Route;

typedef struct Router
{
    Route *head;
} Router;

Router *create_router();
void add_route(Router *router, const char *method, const char *path, Handler handler);
Response handle_request(Router *router, Request *request);
void free_router(Router *router);

#endif // ROUTER