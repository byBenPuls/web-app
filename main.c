#include <stdio.h>
#include "src/router.h"
#include "src/server.h"
#include "src/handlers.h"

const int APP_PORT = 8080;

void include_routers(Router *router)
{
    add_route(router, "*", "/hello", hello_handler);
    add_route(router, "*", "/goodbye", goodbye_handler);
    add_route(router, "*", "/", main_handler);
}


int main()
{
    Router *router = create_router();
    include_routers(router);

    start_server(APP_PORT, router);

    free_router(router);
    return 0;
}