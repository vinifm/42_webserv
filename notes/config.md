## Configuration file requirements
- [ ] Choose the port and host of each ’server’.
- [ ] Setup the server_names or not.
- [ ] The first server for a host:port will be the default for this host:port (that means it will answer to all the requests that don’t belong to an other server).
- [ ] Setup default error pages.
- [ ] Limit client body size.
- [ ] Setup routes with one or multiple of the following rules/configuration (routes wont be using regexp):
	- [ ] define a list of accepted http methods for the route.
	- [ ] define a http redirection.
	- [ ] define a directory or a file from where the file should be searched (for example, if url /kapouet is rooted to /tmp/www, url /kapouet/pouic/toto/pouet is /tmp/www/pouic/toto/pouet).
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
- [ ] files must end with ".conf"

# NGINX configuration
- directives: a statement that controls nginx's behaviour;
- block: group of directives in a context.

### [`listen address[:port]; listen port`](http://nginx.org/en/docs/http/ngx_http_core_module.html#listen)
Sets the address and port for IP. Both address and port, or only address or only port can be specified. An address may also be a hostname.
```
	listen 127.0.0.1:8000;
	listen 127.0.0.1;
	listen 8000;
	listen *:8000;
	listen localhost:8000;
```

### [`server_name name ...;`](http://nginx.org/en/docs/http/ngx_http_core_module.html#server_name)
Define the domain names or IP addresses that a specific server block should respond to. It determines which virtual server configuration should be used to handle incoming requests based on the value of the Host header in the HTTP request.
```
	server_name	example.org
				www.example.org
				""
				192.168.1.1;
```

### [`error_page code ... uri;`](http://nginx.org/en/docs/http/ngx_http_core_module.html#error_page)
Defines the URI that will be shown for the specified errors.
```
	error_page 404				/404.html;
	error_page 500 502 503 504	/50x.html;
```

### [`client_max_body_size size;`](http://nginx.org/en/docs/http/ngx_http_core_module.html#client_max_body_size)
Sets the maximum allowed size of the client request body. If the size in a request exceeds the configured value, the 413 (Request Entity Too Large) error is returned to the client. Please be aware that browsers cannot correctly display this error. Setting size to 0 disables checking of client request body size.

## [`location uri {...}`](http://nginx.org/en/docs/http/ngx_http_core_module.html#location)
Specifies how the server should handle requests for specific URIs.

### [`root path;`](http://nginx.org/en/docs/http/ngx_http_core_module.html#root)
Sets the root directory for requests.
```
	location /i/ {
		root /data/w3;
	}
```
Here, the `/data/w3/i/foo.gif` file will be sent in response to the `/i/foo.gif` request.

### [`limit_except method ...`](http://nginx.org/en/docs/http/ngx_http_core_module.html#limit_except)
Define a list of accepted http methods for the route.
```
	limit_except GET POST;
```
The above example limits all methods *except* GET and POST.
Obs.: syntax is different than Nginx's for the sake of simplicity.

### [`index file ...`](http://nginx.org/en/docs/http/ngx_http_index_module.html#index)
Set a default file to answer if the request is a directory. The first available file is returned.
```
	location /dir {
		index first.html second.html;
	}
```

### [`autoindex on | off;`](http://nginx.org/en/docs/http/ngx_http_autoindex_module.html#autoindex)
Enables or disables the directory listing output. Directory listing displays the contents of a directory when an index file (like index.html) is not found.

### `redirect page`[^1]
Define a http redirection.
```
	location /uri {
		redirect /new/path
	}
```

### `cgi`[^1]
Execute cgi based on certain file extension (for example .php).

## References
- [NGINX: How nginx processes a request;](http://nginx.org/en/docs/http/request_processing.html)
- [NGINX Begginer's Guide: Configuration File’s Structure;](http://nginx.org/en/docs/beginners_guide.html#conf_structure)

[^1]: Custom configuration for this web server. Not available in NGINX.
