#include "router.h"
#include "http.h"
#include "string.h"

Router *create_router()
{
    Router *router = (Router *)malloc(sizeof(Router));
    router->head = NULL;
    return router;
}

void extract_path(const char *url, char *path, size_t path_size)
{
    const char *question_mark = strchr(url, '?');

    if (question_mark != NULL)
    {
        size_t length = question_mark - url;
        if (length < path_size)
        {
            strncpy(path, url, length);
            path[length] = '\0';
        }
        else
        {
            strncpy(path, url, path_size - 1);
            path[path_size - 1] = '\0';
        }
    }
    else
    {
        strncpy(path, url, path_size - 1);
        path[path_size - 1] = '\0';
    }

    size_t path_length = strlen(path);
    if (path_length > 1 && path[path_length - 1] == '/')
    {
        path[path_length - 1] = '\0';
    }
}

void add_route(Router *router, const char *method, const char *path, Handler handler)
{
    Route *new_route = (Route *)malloc(sizeof(Route));
    new_route->path = strdup(path);
    new_route->method = strdup(method);
    new_route->handler = handler;
    new_route->next = router->head;
    router->head = new_route;
}

Response handle_request(Router *router, Request *request)
{
    Route *current = router->head;
    while (current != NULL)
    {
        const char *url = request->path;
        char path[256];
        extract_path(url, path, sizeof(path));
        printf("curr path: %s path: %s\n", current->path, path);
        if (strcmp(current->path, path) == 0)
        {
            if (strcmp(current->method, request->method) == 0 || strcmp(current->method, "*") == 0)
            {
                return current->handler(request);
            }
            return create_response(
                "405 Method Not Allowed",
                "Content-Type: text/plain",
                "Method Not Allowed");
        }
        current = current->next;
    }
    return create_response("404 Not Found",
                           "Content-Type: text/plain",
                           "404 Not Found");
}

void free_router(Router *router)
{
    Route *current = router->head;
    while (current != NULL)
    {
        Route *next = current->next;
        free(current->path);
        free(current);
        current = next;
    }
    free(router);
}