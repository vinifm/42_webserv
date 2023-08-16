# 42_webserv

## Usage

```
./webserv [configuration file]
```

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

## Sockets
A socket is a software abstraction that represents an endpoint for sending or receiving data over a computer network.

- Listening Socket: The web server uses a listening socket to accept incoming connection requests from clients. It listens on a specific port and IP address and waits for clients to establish connections.
- Connected Socket: Once a client initiates a connection to the listening socket, the server creates a new connected socket dedicated to that client. This connected socket is used to send and receive data between the server and the client.

