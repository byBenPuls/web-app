#include "handlers.h"
#include "string.h"
#include "http.h"

Response hello_handler(Request *request)
{
    printf("Request PATH and METHOD: %s %s\n", request->path, request->method);
    return create_response(
        "200 OK",
        "Content-Type: text/html",
        "<!DOCTYPE html>"
        "<html lang=\"en\">"
        "<head><title>Hello Page</title></head>"
        "<body><h1>Hello from C language!</h1><p>Welcome to the Hello Page.</p></body>"
        "</html>");
}

Response goodbye_handler(Request *request)
{
    return create_response("200 OK",
                           "Content-Type: text/plain",
                           "Goodbye, World!");
}

Response main_handler(Request *request)
{
    return create_response(
        "200 OK",
        "Content-Type: text/html",
        "<!DOCTYPE html>"
        "<html lang=\"en\">"
        "<head>"
        "<meta charset=\"UTF-8\">"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
        "<title>Language of Power: C</title>"
        "<style>"
        "body {"
        "margin: 0;"
        "font-family: 'JetBrains Mono', monospace;"
        "background: #1e1e2f;"
        "color: #c5c8c6;"
        "display: flex;"
        "flex-direction: column;"
        "align-items: center;"
        "justify-content: center;"
        "min-height: 100vh;"
        "}"
        "h1 {"
        "color: #8ab4f8;"
        "font-size: 3rem;"
        "margin-bottom: 20px;"
        "text-align: center;"
        "white-space: pre-wrap;"
        "line-height: 1.2;"
        "}"
        "p {"
        "max-width: 600px;"
        "line-height: 1.8;"
        "text-align: center;"
        "margin-bottom: 40px;"
        "color: #b2b2ff;"
        "}"
        ".code-snippet {"
        "background: #282a36;"
        "padding: 20px;"
        "border-radius: 10px;"
        "box-shadow: 0 4px 20px rgba(0, 0, 0, 0.4);"
        "font-size: 1rem;"
        "color: #f8f8f2;"
        "width: 90%;"
        "max-width: 800px;"
        "overflow-x: auto;"
        "line-height: 1.5;"
        "}"
        ".code-snippet span.keyword {"
        "color: #ff79c6;"
        "font-weight: bold;"
        "}"
        ".code-snippet span.function {"
        "color: #50fa7b;"
        "}"
        ".code-snippet span.string {"
        "color: #f1fa8c;"
        "}"
        ".code-snippet span.comment {"
        "color: #6272a4;"
        "font-style: italic;"
        "}"
        ".button {"
        "margin-top: 20px;"
        "text-decoration: none;"
        "color: #282a36;"
        "background: #ff79c6;"
        "padding: 10px 20px;"
        "border-radius: 8px;"
        "font-weight: bold;"
        "transition: all 0.3s;"
        "}"
        ".button:hover {"
        "background: #bd93f9;"
        "color: #1e1e2f;"
        "}"
        "footer {"
        "margin-top: 50px;"
        "font-size: 0.8rem;"
        "color: #6272a4;"
        "text-align: center;"
        "}"
        "@media (max-width: 768px) {"
        "h1 {"
        "font-size: 2rem;"
        "text-align: center;"
        "}"
        "}"
        "</style>"
        "<link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@400;700&display=swap\">"
        "</head>"
        "<body>"
        "<h1>Welcome to the World of C</h1>"
        "<p>C is the language of speed, power, and precision. It’s the foundation of modern computing, bringing systems to life with its elegant simplicity.</p>"
        "<div class=\"code-snippet\">"
        "<pre>"
        "<span class=\"comment\">// This is a simple C program</span><br>"
        "<span class=\"keyword\">#include</span> &lt;stdio.h&gt;<br><br>"
        "<span class=\"keyword\">int</span> <span class=\"function\">main</span>() {<br>"
        "    <span class=\"function\">printf</span>(<span class=\"string\">\"Hello, World!\\n\"</span>);<br>"
        "    <span class=\"keyword\">return</span> <span class=\"keyword\">0</span>;<br>"
        "}"
        "</pre>"
        "</div>"
        "<a href=\"https://en.wikipedia.org/wiki/C_(programming_language)\" target=\"_blank\" class=\"button\">Learn More</a>"
        "<footer>"
        "This website pays homage to the legendary C language—where every bit counts, and elegance meets power. Fun fact: the logic behind this site is also written in C!"
        "</footer>"
        "</body>"
        "</html>");
}

Response json_handler(Request *request)
{
    return create_json_response(
        "200 OK",
        "", //
        "{\"key\":\"value\", \"hello\":\"world\"}");
}