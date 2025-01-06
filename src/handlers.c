#include "handlers.h"
#include "string.h"
#include "http.h"

Response hello_handler(Request *request)
{
    return create_response(
        "200 OK",
        "Content-Type: text/html",
        "<!DOCTYPE html>"
        "<html lang=\"en\">"
        "<head><title>Hello Page</title></head>"
        "<body><h1>Hello, World!</h1><p>Welcome to the Hello Page.</p></body>"
        "</html>");
}

Response goodbye_handler(Request *request)
{
    return create_response("200 OK",
    "Content-Type: text/plain",
    "Goodbye, World!");
}

Response main_handler(Request *request)
{
    return create_response("200 OK",
                           "Content-Type: text/plain",
                           "Welcome to the Main Page!");
}
