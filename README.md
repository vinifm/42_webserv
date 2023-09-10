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

Sources: [FORM TAG](https://www.geeksforgeeks.org/html-form-tag/), [CHUNKED TRANSFER ENCODING](https://en.wikipedia.org/wiki/Chunked_transfer_encoding)
</details>

<details>
<summary>SOCKET</summary>

 A socket is a software abstraction that represents an endpoint for sending or receiving data over a computer network.

- Listening Socket: The web server uses a listening socket to accept incoming connection requests from clients. It listens on a specific port and IP address and waits for clients to establish connections.
- Connected Socket: Once a client initiates a connection to the listening socket, the server creates a new connected socket dedicated to that client. This connected socket is used to send and receive data between the server and the client.

</details>
<details>
<summary>MULTIPLEXING(I/O)/EPOLL</summary>
## PIPES & NON-BLOCKING MANNER SERVER
It's a tube for communication between proccess.
They use read and write functions to realize the data transference.

- blocking-pipes: When you try to read a empty pipe the program will block and wait until the pipe have something, or when you try to write a full pipe, it will block until the pipe free space.
- non-blocking-pipes: When you try to read a empty pipe, a message will be returned saying that the pipe is empty and the program will continue. If the pipe is full, the program will continue and a message will be presented that the pipe is full.

## poll() and epoll()
poll() and epoll() are both I/O multiplexing mechanisms used in programming for efficiently handling multiple I/O sources, such as sockets, in a non-blocking manner. They are particularly useful in networking applications to manage and monitor multiple connections simultaneously. However, they have different implementations and capabilities, primarily based on the operating system they are designed for.

- Connection Management:
	- poll(): Requires manual management of the descriptor set for new connections and disconnections.
	- epoll(): Allows dynamic addition and removal of descriptors, simplifying connection handling.

- Scalability:
	- poll(): Performance can degrade as the number of clients increases due to linear scanning.
	- epoll(): Scales efficiently for a large number of clients, making it suitable for high-connection scenarios.

- Data Processing:
	- poll(): Requires efficient reading/writing of data to avoid excessive notifications.
	- epoll(): Offers more granular control over data processing, minimizing overconsumption.

- CPU Usage:
	- poll(): Can result in higher CPU usage as the number of clients grows.
	- epoll(): Provides efficient event handling, reducing CPU usage and improving scalability.

- Event Notification:
	- poll(): Provides level-triggered event notification, which can lead to unnecessary notifications.
	- epoll(): Supports both level-triggered and edge-triggered notification, reducing unnecessary notifications.

### Level-triggered vs. Edge-triggered notifications
- Level-triggered notifications generate events while the monitored condition remains true (e.g. data can be read), leading to continuous notifications until the condition changes.
- Edge-triggered notifications generate events only when there's a change in the monitored condition, making them more efficient in terms of notification frequency and CPU usage.

By contrast, when epoll is used as a level-triggered interface (the default, when EPOLLET is not specified), it is simply a faster poll(2), and can be used wherever the latter is used since it shares the same semantics.

Manual pages:
- [poll()](https://man7.org/linux/man-pages/man2/poll.2.html)
- [epoll()](https://man7.org/linux/man-pages/man7/epoll.7.html)
</details>
<hr> 
<details>
<summary>CGI(PYTHON)</summary>

</details>
