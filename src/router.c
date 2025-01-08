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
    return create_response(
        "404 Not Found",
        "Content-Type: text/html",
        "<!DOCTYPE html>"
        "<html lang=\"en\">"
        "<head>"
        "<meta charset=\"UTF-8\">"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
        "<title>404 - Page Not Found</title>"
        "<style>"
        "body {"
        "margin: 0;"
        "font-family: 'JetBrains Mono', monospace;"
        "background: #1e1e2f;"
        "color: #c5c8c6;"
        "display: flex;"
        "flex-direction: column;"
        "align-items: center;"
        "justify-content: center;"
        "min-height: 100vh;"
        "text-align: center;"
        "}"
        "h1 {"
        "color: #ff5555;"
        "font-size: 4rem;"
        "margin-bottom: 20px;"
        "text-shadow: 0 0 10px #ff5555;"
        "}"
        "p {"
        "font-size: 1.5rem;"
        "color: #f1fa8c;"
        "margin-bottom: 40px;"
        "}"
        ".button {"
        "margin-top: 20px;"
        "text-decoration: none;"
        "color: #282a36;"
        "background: #ff79c6;"
        "padding: 10px 20px;"
        "border-radius: 8px;"
        "font-weight: bold;"
        "transition: all 0.3s;"
        "}"
        ".button:hover {"
        "background: #bd93f9;"
        "color: #1e1e2f;"
        "}"
        "footer {"
        "margin-top: 50px;"
        "font-size: 0.8rem;"
        "color: #6272a4;"
        "text-align: center;"
        "}"
        "</style>"
        "<link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@400;700&display=swap\">"
        "</head>"
        "<body>"
        "<h1>404</h1>"
        "<p>The page you're looking for doesn't exist. But don't worry, the C language never forgets its roots!</p>"
        "<a href=\"/\" class=\"button\">Go Back Home</a>"
        "<footer>"
        "This 404 page is handcrafted with C, honoring the language that makes the impossible possible."
        "</footer>"
        "</body>"
        "</html>");
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