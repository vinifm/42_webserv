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
[ ] files must end with ".conf"

## nginx configuration
- directives: a statement that controls nginx's behaviour;
- block: group of directives in a context.

- **`listen`**: Sets the address and port for IP. Both address and port, or only address or only port can be specified. An address may also be a hostname.
```
	listen 127.0.0.1:8000;
	listen 127.0.0.1;
	listen 8000;
	listen *:8000;
	listen localhost:8000;
```

- **`location`**: specifies how the server should handle requests for specific URIs.
- **`root`**: Sets the root directory for requests.
```
	location /i/ {
		root /data/w3;
	}
```
Here, the `/data/w3/i/foo.gif` file will be sent in response to the `/i/foo.gif` request.

## References
- [NGINX Begginer's Guide: Configuration File’s Structure;](http://nginx.org/en/docs/beginners_guide.html#conf_structure)
- [NGINX: How nginx processes a request;](http://nginx.org/en/docs/http/request_processing.html)
- [Digital Ocean: Understanding the Nginx Configuration File Structure and Configuration Contexts;](https://www.digitalocean.com/community/tutorials/understanding-the-nginx-configuration-file-structure-and-configuration-contexts)
