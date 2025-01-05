#include "router.h"

Router *create_router()
{
    Router *router = (Router *)malloc(sizeof(Router));
    router->head = NULL;
    return router;
}

void add_route(Router *router, const char *path, Handler handler)
{
    Route *new_route = (Route *)malloc(sizeof(Route));
    new_route->path = strdup(path);
    new_route->handler = handler;
    new_route->next = router->head;
    router->head = new_route;
}

void handle_request(Router *router, const char *path, char *response, size_t response_size)
{
    Route *current = router->head;
    while (current != NULL)
    {
        if (strcmp(current->path, path) == 0)
        {
            current->handler(response, response_size); // Передаем буфер ответа
            return;
        }
        current = current->next;
    }
    snprintf(response, response_size, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found");
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