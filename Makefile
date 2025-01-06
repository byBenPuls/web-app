CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = application

SRCS = main.c src/router.c src/handlers.c src/server.c src/http.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LUBUV)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LUBUV)
# also maybe for threads:
# gcc main.c src/router.c src/handlers.c src/server.c src/http.c -o application -lpthread

run:
	docker-compose build
	docker-compose up

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean