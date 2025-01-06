#include "router.h"
#include "http.h"

Router *create_router()
{
    Router *router = (Router *)malloc(sizeof(Router));
    router->head = NULL;
    return router;
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
        if (strcmp(current->path, request->path) == 0)
        {
            if (strcmp(current->method, request->method) == 0 || strcmp(current->method, "*") == 0)
            {
                return current->handler(request); // Передаем буфер ответа
            }
            return create_response(
                "405 Method Not Allowed",
                "Content-Type: text/plain",
                "⚠️⚠️⚠️⚠️ не тот метод ты выбрал.."
            );
        }
        current = current->next;
    }
    return create_response("404 Not Found",
    "Content-Type: text/plain",
    "404 Not Found"
    );
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