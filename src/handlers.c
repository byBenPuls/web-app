#include "handlers.h"
#include "string.h"

void hello_handler(char *response, size_t response_size)
{
    const char *html_template =
        "<!DOCTYPE html>"
        "<html lang=\"en\">"
        "<head>"
        "<meta charset=\"UTF-8\">"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
        "<title>Hello Page</title>"
        "</head>"
        "<body>"
        "<h1>Hello, World!</h1>"
        "<p>Welcome to the Hello Page.</p>"
        "</body>"
        "</html>";

    snprintf(response, response_size,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %zu\r\n"
             "\r\n"
             "%s",
             strlen(html_template), html_template);
}

void goodbye_handler(char *response, size_t response_size)
{
    snprintf(response, response_size, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nGoodbye, World!");
}

void main_handler(char *response, size_t response_size)
{
    snprintf(response, response_size, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nWelcome to the Main Page!");
}
