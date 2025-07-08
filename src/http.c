#include "http.h"
#include "http/statuses.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_request(const char *request_str, Request *request) {
	char *request_copy = strdup(request_str);
	if (!request_copy) {
		return -1;
	}

	char *line = strtok(request_copy, "\r\n");

	if (sscanf(line, "%15s %255s", request->method, request->path) != 2) {
		free(request_copy);
		return -1;
	}

	request->header_count = 0;

	while ((line = strtok(NULL, "\r\n")) != NULL) {
		if (request->header_count < MAX_HEADER_COUNT) {
			strncpy(request->headers[request->header_count], line,
					MAX_HEADER_LENGTH - 1);
			request->headers[request->header_count][MAX_HEADER_LENGTH - 1] =
				'\0';
			request->header_count++;
		}
	}

	free(request_copy);
	return 0;
}

Response create_response(const char *status, const char *headers,
						 const char *body) {
	if (body == NULL || status == NULL || headers == NULL) {
		printf("Internal service error\n");

		Response error_response;
		error_response.status = strdup(HTTP_500_INTERNAL_SERVER_ERROR);
		error_response.headers = strdup("Content-Type: text/html");
		error_response.body = strdup("Internal server error");
		return error_response;
	}

	Response response;
	response.status = strdup(status);
	response.headers = strdup(headers);
	response.body = strdup(body);

	return response;
}

Response create_json_response(const char *status, const char *headers,
							  const char *json) {
	char type[2048] = "Content-Type: application/json";
	char modified_headers[2048];
	if (strcmp(headers, "") == 0) {
		strcpy(modified_headers, type);
	} else {
		strcpy(modified_headers, strcat(type, "\r\n"));
		strcat(modified_headers, headers);
	}
	return create_response(status, modified_headers, json);
}

void free_json_response(JsonResponse *json_response) {
	free(json_response->status);
	free(json_response->headers);
	free(json_response->json);
}

void free_response(Response *response) {
	free(response->status);
	free(response->headers);
	free(response->body);
}
