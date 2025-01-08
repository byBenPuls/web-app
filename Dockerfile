FROM gcc:latest

WORKDIR /application

COPY . ./

RUN gcc -Wall -Wextra -g main.c src/router.c src/handlers.c src/server.c src/http.c -o application
CMD ["/bin/bash", "entrypoint.sh"]