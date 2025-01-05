# Web-app
A simple web application on ~~Fortran~~ C for windows.


### How to setup?

First, download C compiler (GCC for example). Then, check `Ws2_32.lib` and `winsock2`.
After that, you can deploy server:

```bash
>>> make
```

Finally, you compiled server. You can run the server:

```bash
>>> .\application.exe
```

Server will be available on **127.0.0.1:8080**.