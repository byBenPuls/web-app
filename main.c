#include <stdio.h>
#include "src/router.h"
#include "src/server.h"
#include "src/handlers.h"


void include_routers(Router *router)
{
    add_route(router, "hello", hello_handler);
    add_route(router, "goodbye", goodbye_handler);
    add_route(router, "", main_handler);
}


int main()
{
    Router *router = create_router();
    include_routers(router);

    start_server(8080, router);

    free_router(router);
    return 0;
}