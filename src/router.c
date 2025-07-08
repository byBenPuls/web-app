#include "router.h"
#include "http.h"
#include "http/statuses.h"
#include "page_reader.h"
#include "string.h"

Router *create_router() {
	Router *router = (Router *)malloc(sizeof(Router));
	router->head = NULL;
	return router;
}

void extract_path(const char *url, char *path, size_t path_size) {
	const char *question_mark = strchr(url, '?');

	if (question_mark != NULL) {
		size_t length = question_mark - url;
		if (length < path_size) {
			strncpy(path, url, length);
			path[length] = '\0';
		} else {
			strncpy(path, url, path_size - 1);
			path[path_size - 1] = '\0';
		}
	} else {
		strncpy(path, url, path_size - 1);
		path[path_size - 1] = '\0';
	}

	size_t path_length = strlen(path);
	if (path_length > 1 && path[path_length - 1] == '/') {
		path[path_length - 1] = '\0';
	}
}

void add_route(Router *router, const char *method, const char *path,
			   Handler handler) {
	Route *new_route = (Route *)malloc(sizeof(Route));
	new_route->path = strdup(path);
	new_route->method = strdup(method);
	new_route->handler = handler;
	new_route->next = router->head;
	router->head = new_route;
}

Response handle_request(Router *router, Request *request) {
	Route *current = router->head;
	while (current != NULL) {
		const char *url = request->path;
		char path[256];
		extract_path(url, path, sizeof(path));
		if (strcmp(current->path, path) == 0) {
			if (strcmp(current->method, request->method) == 0 ||
				strcmp(current->method, "*") == 0) {
				return current->handler(request);
			}
			return create_response(HTTP_405_METHOD_NOT_ALLOWED,
								   "Content-Type: text/plain",
								   "Method Not Allowed");
		}
		current = current->next;
	}
	return create_response(HTTP_404_NOT_FOUND, "Content-Type: text/html",
						   read_page("src/pages/not_found.html"));
}

void free_router(Router *router) {
	Route *current = router->head;
	while (current != NULL) {
		Route *next = current->next;
		free(current->path);
		free(current);
		current = next;
	}
	free(router);
}
