#include "src/handlers.h"
#include "src/http/router.h"
#include "src/http/server.h"
#include <stdio.h>

const int APP_PORT = 8080;
const char *APP_HOST = "0.0.0.0";

void include_routers(Router *router) {
	add_route(router, "*", "/hello", hello_handler);
	add_route(router, "*", "/goodbye", goodbye_handler);
	add_route(router, "*", "/", main_handler);
	add_route(router, "GET", "/json", json_handler);
}

int main() {
	Router *router = create_router();
	include_routers(router);

	start_server(APP_PORT, APP_HOST, router);

	free_router(router);
	return 0;
}
