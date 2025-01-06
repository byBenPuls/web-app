#include "handlers.h"
#include "string.h"
#include "http.h"

Response hello_handler(Request *request)
{
    printf("Request PATH and METHOD: %s %s\n", request->path, request->method);
    return create_response(
        "200 OK",
        "Content-Type: text/html",
        "<!DOCTYPE html>"
        "<html lang=\"en\">"
        "<head><title>Hello Page</title></head>"
        "<body><h1>Hello from C language!</h1><p>Welcome to the Hello Page.</p></body>"
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

Response json_handler(Request *request)
{
    return create_json_response(
        "200 OK",
        "", //
        "{\"key\":\"value\", \"hello\":\"world\"}");
}