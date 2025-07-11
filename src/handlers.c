#include "handlers.h"
#include "http.h"
#include "http/statuses.h"
#include "page_reader.h"

Response hello_handler(Request *request) {
	printf("Request PATH and METHOD: %s %s\n", request->path, request->method);
	return create_response(HTTP_200_OK, "Content-Type: text/html",
						   read_page("src/pages/hello.html"));
}

Response goodbye_handler(Request *request) {
	return create_response(HTTP_200_OK, "Content-Type: text/plain",
						   "Goodbye, World!");
}

Response main_handler(Request *request) {
	return create_response(HTTP_200_OK, "Content-Type: text/html",
						   read_page("src/pages/main.html"));
}

Response json_handler(Request *request) {
	return create_json_response(HTTP_200_OK, "",
								"{\"key\":\"value\", \"hello\":\"world\"}");
}
