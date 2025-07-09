CC = gcc
CFLAGS = -Wall -Wextra -g -lpthread

TARGET = application

SRCS = main.c src/http/router.c src/handlers.c src/http/server.c src/http/http.c src/http/page_reader.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
# also maybe for threads:
# gcc main.c src/router.c src/handlers.c src/server.c src/http.c -o application -lpthread

run:
	docker-compose -f "docker-compose.yml" up -d --build 

down:
	docker-compose -f "docker-compose.yml" down

restart: run down

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
