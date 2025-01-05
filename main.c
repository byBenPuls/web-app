#include <stdio.h>
#include "src/router.h"
#include "src/server.h"
#include "src/handlers.h"

int main()
{
    Router *router = create_router();
    add_route(router, "hello", hello_handler);
    add_route(router, "goodbye", goodbye_handler);

    start_server(8080, router);

    free_router(router);
    return 0;
}