#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"

int parse_request(const char *request_str, Request *request)
{
    char *request_copy = strdup(request_str);
    if (!request_copy)
    {
        return -1;
    }

    char *line = strtok(request_copy, "\r\n");

    if (sscanf(line, "%s %s", request->method, request->path) != 2)
    {
        free(request_copy);
        return -1;
    }

    request->header_count = 0;

    while ((line = strtok(NULL, "\r\n")) != NULL)
    {
        if (request->header_count < MAX_HEADER_COUNT)
        {
            strncpy(request->headers[request->header_count], line, MAX_HEADER_LENGTH - 1);
            request->headers[request->header_count][MAX_HEADER_LENGTH - 1] = '\0';
            request->header_count++;
        }
    }

    free(request_copy);
    return 0;
}

Response create_response(const char *status, const char *headers, const char *body)
{
    Response response;
    response.status = strdup(status);
    response.headers = strdup(headers);
    response.body = strdup(body);
    return response;
}

void free_response(Response *response)
{
    free(response->status);
    free(response->headers);
    free(response->body);
}

const char *get_http_status_message(int status_code)
{
    switch (status_code)
    {
    case 200:
        return "200 OK";
    case 201:
        return "201 Created";
    case 202:
        return "202 Accepted";
    case 204:
        return "204 No Content";
    case 301:
        return "301 Moved Permanently";
    case 302:
        return "302 Found";
    case 303:
        return "303 See Other";
    case 304:
        return "304 Not Modified";
    case 307:
        return "307 Temporary Redirect";
    case 308:
        return "308 Permanent Redirect";
    case 400:
        return "400 Bad Request";
    case 401:
        return "401 Unauthorized";
    case 403:
        return "403 Forbidden";
    case 404:
        return "404 Not Found";
    case 405:
        return "405 Method Not Allowed";
    case 408:
        return "408 Request Timeout";
    case 409:
        return "409 Conflict";
    case 410:
        return "410 Gone";
    case 415:
        return "415 Unsupported Media Type";
    case 429:
        return "429 Too Many Requests";
    case 500:
        return "500 Internal Server Error";
    case 501:
        return "501 Not Implemented";
    case 502:
        return "502 Bad Gateway";
    case 503:
        return "503 Service Unavailable";
    case 504:
        return "504 Gateway Timeout";
    default:
        return "Unknown Status";
    }
}