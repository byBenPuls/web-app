#ifndef HANDLERS_H
#define HANDLERS_H

#include <stdio.h>
#include "http.h"

Response hello_handler(Request *request);
Response goodbye_handler(Request *request);
Response main_handler(Request *request);
Response json_handler(Request *request);

#endif // HANDLERS_H