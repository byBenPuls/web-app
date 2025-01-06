#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_METHOD_LENGTH 10
#define MAX_PATH_LENGTH 1024
#define MAX_HEADER_COUNT 50
#define MAX_HEADER_LENGTH 256

const char *get_http_status_message(int status_code);

typedef struct
{
    char method[MAX_METHOD_LENGTH];
    char path[MAX_PATH_LENGTH];
    char headers[MAX_HEADER_COUNT][MAX_HEADER_LENGTH];
    int header_count;
} Request;

typedef struct
{
    char *status;
    char *headers;
    char *body;
} Response;

typedef struct
{
    char *status;
    char *headers;
    char *json;
} JsonResponse;

int parse_request(const char *request_str, Request *request);

Response create_response(const char *status, const char *headers, const char *body);
Response create_json_response(const char *status, const char *headers, const char *json);
void free_response(Response *response);
void free_json_response(JsonResponse *response);

#endif