# WEBSERV (by vini, lipi & acapela-)

<details>
<summary>PARSER (CONFIGURATION FILE) vini</summary>

## Configuration file requirements
- [ ] Choose the port and host of each ’server’.
- [ ] Setup the server_names or not.
- [ ] The first server for a host:port will be the default for this host:port (that means it will answer to all the requests that don’t belong to an other server).
- [ ] Setup default error pages.
- [ ] Limit client body size.
- [ ] Setup routes with one or multiple of the following rules/configuration (routes wont be using regexp):
	- [ ] define a list of accepted http methods for the route.
	- [ ] define a http redirection.
	- [ ] define a directory or a file from where the file should be searched (for example, if url /kapouet is rooted to /tm	/www, url /kapouet/pouic/toto/pouet is /tmp/www/pouic/toto/pouet).
	- [ ] turn on or off directory listing.
	- [ ] set a default file to answer if the request is a directory.
	- [ ] execute cgi based on certain file extension (for example .php).
	- [ ] make it work with post and get methods.
	- [ ] make the route able to accept uploaded files and configure where they should be saved.

- [ ] do you wonder what a cgi is?
- [ ] because you won’t call the cgi directly, use the full path as path_info.
- [ ] just remember that, for chunked request, your server needs to unchunk it, the cgi will expect eof as end of the body.
- [ ] same things for the output of the cgi. if no content_length is returned from the cgi, eof will mark the end of the returned data.
- [ ] your program should call the cgi with the file requested as first argument.
- [ ] the cgi should be run in the correct directory for relative path file access.
- [ ] your server should work with one cgi (php-cgi, python, and so forth).

## error management
- [x] files must end with ".conf"
- [x] root path must end with "/"
- [x] location prefix must start with "/"
- [x] server block must have root and index directives;
- [ ]
- [ ] directives must not be empty
	- [x] listen

# NGINX configuration
- directives: a statement that controls nginx's behaviour;
- block: group of directives in a context.

## Contexts:
If not specified in a location block, server directives are used. If also not specified, default values are considered.

| Directive | Default | Quantity | Server | Location |
|---|---|---|---|---|
| [listen](#listen-addressport-listen-port)				| `listen *:80`				| 1+ | :white_check_mark:	| :x: |
| [server_name](#server_name-name)						| `server_name ""`			| 0-1 | :white_check_mark:	| :x: |
| [location](#location-uri)								| `---`						| 1+ | :white_check_mark:	| :x:[^1] |
| [error_page](#error_page-code--uri)					| `---`						| 1+ | :white_check_mark:	| :x: |
| [client_max_body_size](#client_max_body_size-size)	| `client_max_body_size 1m`	| 1 | :white_check_mark:	| :x: |
| [root](#root-path)									| `root html`				| 1 | :white_check_mark:	| :white_check_mark: |
| [index](#index-file)									| `index index.html`		| 1 | :x:					| :white_check_mark: |
| [autoindex](#autoindex-on--off)						| `autoindex off`			| 1 | :x:					| :white_check_mark: |
| [limit_except](#limit_except-method)					| `---`						| 1 | :x:					| :white_check_mark: |
| [redirect](#redirect-page1)							| `---`						| 1 | :x:					| :white_check_mark: |

### [`listen address[:port]; listen port`](http://nginx.org/en/docs/http/ngx_http_core_module.html#listen)
Default: `listen *:80 | *:8000`

Sets the address and port for IP. Both address and port, or only address or only port can be specified. An address may also be a hostname.
```
	listen 127.0.0.1:80
	listen 127.0.0.1
	listen 80
	listen *:8000
	listen localhost:80
```

### [`server_name name ...;`](http://nginx.org/en/docs/http/ngx_http_core_module.html#server_name)
Default: `server_name ""`

Define the domain names or IP addresses that a specific server block should respond to. It determines which virtual server configuration should be used to handle incoming requests based on the value of the Host header in the HTTP request.
```
	server_name	example.org
				www.example.org
				""
				192.168.1.1
```

### [`root path;`](http://nginx.org/en/docs/http/ngx_http_core_module.html#root)
Default: `root html`

Sets the root directory for requests.
```
	location /i/ {
		root /data/w3
	}
```
Here, the `/data/w3/i/foo.gif` file will be sent in response to the `/i/foo.gif` request.

### [`index file ...`](http://nginx.org/en/docs/http/ngx_http_index_module.html#index)
Default: `index index.html`

Set a default file to answer if the request is a directory. The first available file is returned.
```
	location /dir {
		index first.html second.html
	}
```

### [`autoindex on | off;`](http://nginx.org/en/docs/http/ngx_http_autoindex_module.html#autoindex)
Default: `autoindex off`

Enables or disables the directory listing output. Directory listing displays the contents of a directory when an index file (like index.html) is not found.

### [`error_page code ... uri;`](http://nginx.org/en/docs/http/ngx_http_core_module.html#error_page)
Default: `---`

Defines the URI that will be shown for the specified errors.
```
	error_page 404				/404.html
	error_page 500 502 503 504	/50x.html
```

### [`client_max_body_size size;`](http://nginx.org/en/docs/http/ngx_http_core_module.html#client_max_body_size)
Default: `client_max_body_size 1m`

Sets the maximum allowed size of the client request body. If the size in a request exceeds the configured value, the 413 (Request Entity Too Large) error is returned to the client. Please be aware that browsers cannot correctly display this error. Setting size to 0 disables checking of client request body size.

### `cgi`[^2]
Execute cgi based on certain file extension (for example .php).

## [`location uri {...}`](http://nginx.org/en/docs/http/ngx_http_core_module.html#location)
Default: `---`

Specifies how the server should handle requests for specific URIs.

### [`limit_except method ...`](http://nginx.org/en/docs/http/ngx_http_core_module.html#limit_except)
Default: `---`

Define a list of accepted http methods for the route.
```
	limit_except GET POST
```
The above example limits all methods *except* GET and POST.
Obs.: syntax is different than Nginx's for the sake of simplicity.

### `redirect page`[^2]
Default: `---`

Define a http redirection.
```
	location /uri {
		redirect /new/path
	}
```

## References
- [NGINX: How nginx processes a request;](http://nginx.org/en/docs/http/request_processing.html)
- [NGINX Begginer's Guide: Configuration File’s Structure;](http://nginx.org/en/docs/beginners_guide.html#conf_structure)

[^1]: For the sake of simplicity, the location directive is only available in the server context.
[^2]: Custom configuration for this web server. Not available in NGINX.

</details>

<hr>
acapela-
<details>
<summary>HTTP</summary>

#### What is HTTP in simple terms?
* Hypertext Transfer Protocol
* It's a group of rules used by all browsers for comunicate hypertext between internet in a high efficient way and easy to work.

#### How it works?
* It's a talk between server (application responsible to serve datas) and client (browser, responsible for ask resources in network, calling theirs names, the known URLs).
* The message sent by client is a request 'pedido', while the message sent by server is called response 'resposta'.
* Client ask some resource the server proccess and return a response containing the requested resource or information.
* The communication will be successfull if the the messages follow a specific format specified by the HTTP procotol present in HTML [RFC](https://datatracker.ietf.org/doc/html/rfc2616) standard.

#### 'HTTP REQUEST' sample?
```
GET /inicio.html HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,/;q=0.8
Accept-Language: en-GB,en;q=0.5
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
```

#### 'HTTP RESPONSE' sample?
```
HTTP/1.1 200 OK
Date:  Mon, 23 May 2005 22:38:34 GMT
Content-Type:  text/html; charset=UTF-8
Content-Length:  155
Last-Modified:  Wed, 08 Jan 2003 23:11:55 GMT
Server:   Apache/1.3.3.7 (Unix) (Red-Hat/Linux)
ETag:  "3f80f-1b6-3e1cb03b"
Accept-Ranges:  bytes
Connection:  close
# WEBSERV (by vini, lipi & acapela-)

<details>
<summary>PARSER (CONFIGURATION FILE)</summary>

</details>

<hr>

<details>
<summary>HTTP</summary>

#### What is HTTP in simple terms?
* Hypertext Transfer Protocol
* It's a group of rules used by all browsers for comunicate hypertext between internet in a high efficient way and easy to work.

#### How it works?
* It's a talk between server (application responsible to serve datas) and client (browser, responsible for ask resources in network, calling theirs names, the known URLs).
* The message sent by client is a request 'pedido', while the message sent by server is called response 'resposta'.
* Client ask some resource the server proccess and return a response containing the requested resource or information.
* The communication will be successfull if the the messages follow a specific format specified by the HTTP procotol present in HTML [RFC](https://datatracker.ietf.org/doc/html/rfc2616) standard.

#### 'HTTP REQUEST' sample?
```
GET /inicio.html HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,/;q=0.8
Accept-Language: en-GB,en;q=0.5
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
```

#### 'HTTP RESPONSE' sample?
```
HTTP/1.1 200 OK
Date:  Mon, 23 May 2005 22:38:34 GMT
Content-Type:  text/html; charset=UTF-8
Content-Length:  155
Last-Modified:  Wed, 08 Jan 2003 23:11:55 GMT
Server:   Apache/1.3.3.7 (Unix) (Red-Hat/Linux)
ETag:  "3f80f-1b6-3e1cb03b"
Accept-Ranges:  bytes
Connection:  close

<html>
<head>
      <title>An Example Page</title>
</head>
<body>
     <p>Hello World, this is a very simple HTML document.</p>
</body>
</html>
```
Sources: [HTTP](https://en.wikipedia.org/wiki/HTTP), [CRUD](https://en.wikipedia.org/wiki/Create,_read,_update_and_delete), [MIME](https://en.wikipedia.org/wiki/Media_type), [RFC](https://en.wikipedia.org/wiki/Request_for_Comments), [HTTP HEADER FIELDS](https://en.wikipedia.org/wiki/List_of_HTTP_header_fields)

## Http Methods(Or verbs) (What they do? How they works?)
They are used to indicate the action to be executed in server.

- GET: Get informations from some resource in Server.
- HEAD: Similar to GET, but just get the header of resource and not the body. *So it seeks to obtain specific informations about resource and not print it on screen.*
- POST: Send data to Server proccess. It can create or update a resource.
- PUT: Used to update a resource on server. It replace (override) completely the resource.
- PATCH: Used to modify one part of some resource in server.
- DELETE: Delete a resource in server.
- OPTIONS: Obtain details about some resource on server, such as: allowed HTTP VERBS and others details.
- CONNECT: Less common, it is used to connect with a resource. It is common when the client wants to work with proxy server etc.
- TRACE: Also less common, retrieve information about the requests and response of certain resource on server.

> **Idempotent:** Is a method that when you executed it a lot of times in sequence, is the same that executed one time, because after the first, using the same dates the result is nothing. POST is the only No idempotent HTTP method, because a sequence of calling with the same datas will create different resources and different actions.

## Http Response Status

 - 10x: Just informative answer;
   - 100:
   - 101:
   - 102:
   - 103:
 - 20x: Success answer;
   - 200:
     - GET:
     - HEAD:
     - PUT OU POST:
     - TRACE:
   - 201:
   - 202:
   - 203:
   - 204:
   - 205:
   - 206:
   - 207:
   - 208:
   - 226:
 - 30x: Redirection Error;
   - 300:
   - 301:
   - 302:
   - 303:
   - 304:
   - 305:
   - 306:
   - 307:
   - 308:
 - 40x: Client Error;
   - 400:
   - 401:
   - 402:
   - 403 (Forbidden): Client is not authorized do access the requested resource (autoindex off on certain route, and you try to access a directory).
   - 404 (Not found): URL don't exist.
   - 405:
   - 406:
   - 407:
   - 408:
   - 409:
   - 410:
   - 423:
   - 424:
   - 425:
   - 426:
   - 428:
   - 429:
   - 431:
   - 451:
- 50x: Server Error;
   - 500:
   - 501:
   - 502:
   - 503:
   - 504:
   - 505:
   - 506:
   - 507:
   - 508:
   - 510:
   - 511:

## HANDLING POST METHOD
Now let's understand how can I receive a POST REQUEST from Server and proccess it? Let's first analyse an file upload operation.

1. Use \<form\> tag with proper attributes in post mode and click on some submit button.
2. You will receive the following http header and body:
```
POST /upload HTTP/1.1
Host: localhost:8080
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/117.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: pt-BR,pt;q=0.8,en-US;q=0.5,en;q=0.3
Accept-Encoding: gzip, deflate, br
Content-Type: multipart/form-data; boundary=---------------------------8576620533433054745278394201
Content-Length: 61
Origin: http://localhost:8080
Connection: keep-alive
Referer: http://localhost:8080/upload
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: same-origin
Sec-Fetch-User: ?1

-----------------------------8576620533433054745278394201--
```
3. ...

> **Chunked Transfer Encoding:** Technic used for transfer files to server.

## What is an HTTP server?
The primary function of a web server is to store, process, and deliver web pages to clients (usually web browsers). The communication between client and server takes place using the Hypertext Transfer Protocol (HTTP).

When you type a website's URL into your web browser and hit Enter, your browser sends an HTTP request to a web server. The HTTP server processes the request and returns an HTTP response containing the requested resource, which your browser then displays.

## What are RFCs?
RFC stands for "Request for Comments." In the context of computer networking and the internet, an RFC is a document that describes standards, protocols, procedures, and other technical specifications. RFCs are developed and published by the Internet Engineering Task Force (IETF), which is a community-driven organization responsible for developing and maintaining many of the fundamental protocols and standards that underpin the internet.

- [RFC 9110: HTTP Semantics.](https://www.rfc-editor.org/rfc/rfc9110.html)
- [RFC 9112: HTTP/1.1](https://www.rfc-editor.org/rfc/rfc9112.html)

## What is NGINX?
NGINX is open source software for web serving, reverse proxying, caching, load balancing, media streaming, and more. See:
[Documentation on how to configure NGINX as a web server](https://docs.nginx.com/nginx/admin-guide/web-server/#nginx--admin-guide--basic-functionality).

# I/O Operations

## Multiplexing
I/O multiplexing is a technique used in computer programming to efficiently handle multiple I/O operations (such as reading from or writing to files, sockets, or other input/output sources) without blocking the program's execution. It allows a single process to manage and monitor multiple I/O sources simultaneously and determine which ones are ready for data transfer, without waiting for each I/O operation to complete before moving on to the next.

 - 10x: Just informative answer;
	 - 100:
	 - 101:
	 - 102:
	 - 103:
 - 20x: Success answer;
	 - 200:
		 - GET:
		 - HEAD:
		 - PUT OU POST:
		 - TRACE:
	 - 201:
	 - 202:
	 - 203:
	 - 204:
	 - 205:
	 - 206:
	 - 207:
	 - 208:
	 - 226:
 - 30x: Redirection Error;
	 - 300:
	 - 301:
	 - 302:
	 - 303:
	 - 304:
	 - 305:
	 - 306:
	 - 307:
	 - 308:
 - 40x: Client Error;
	 - 400:
	 - 401:
	 - 402:
	 - 403 (Forbidden): Client is not authorized do access the requested resource (autoindex off on certain route, and you try to access a directory).
	 - 404 (Not found): URL don't exist.
	 - 405:
	 - 406:
	 - 407:
	 - 408:
	 - 409:
	 - 410:
	 - 423:
	 - 424:
	 - 425:
	 - 426:
	 - 428:
	 - 429:
	 - 431:
	 - 451:
- 50x: Server Error;
	 - 500:
	 - 501:
	 - 502:
	 - 503:
	 - 504:
	 - 505:
	 - 506:
	 - 507:
	 - 508:
	 - 510:
	 - 511:

## HANDLING POST METHOD
Now let's understand how can I receive a POST REQUEST from Server and proccess it? Let's first analyse an file upload operation.

1. Use \<form\> tag with proper attributes in post mode and click on some submit button.
2. You will receive the following http header and body:
```
POST /upload HTTP/1.1
Host: localhost:8080
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/117.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: pt-BR,pt;q=0.8,en-US;q=0.5,en;q=0.3
Accept-Encoding: gzip, deflate, br
Content-Type: multipart/form-data; boundary=---------------------------8576620533433054745278394201
Content-Length: 61
Origin: http://localhost:8080
Connection: keep-alive
Referer: http://localhost:8080/upload
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: same-origin
Sec-Fetch-User: ?1

-----------------------------8576620533433054745278394201--
```
3. ...

> **Chunked Transfer Encoding:** Technic used for transfer files to server.

Sources: [FORM TAG](https://www.geeksforgeeks.org/html-form-tag/), [CHUNKED TRANSFER ENCODING](https://en.wikipedia.org/wiki/Chunked_transfer_encoding)
</details>

<details>
<summary>SOCKET</summary>


Manual pages:
- [poll()](https://man7.org/linux/man-pages/man2/poll.2.html)
- [epoll()](https://man7.org/linux/man-pages/man7/epoll.7.html)

## Sockets
A socket is a software abstraction that represents an endpoint for sending or receiving data over a computer network.

- Listening Socket: The web server uses a listening socket to accept incoming connection requests from clients. It listens on a specific port and IP address and waits for clients to establish connections.
- Connected Socket: Once a client initiates a connection to the listening socket, the server creates a new connected socket dedicated to that client. This connected socket is used to send and receive data between the server and the client.

