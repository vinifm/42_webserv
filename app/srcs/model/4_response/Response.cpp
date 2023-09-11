#include <Response.hpp>

//occf
Response::Response(std::map<int, std::string> http_codes) : _http_codes(http_codes)
{
	this->_statusLine = new StatusLine();
	this->_statusLine->setProtocol("HTTP/1.1");
	this->_statusLine->setCode(this->_http_codes.find(200));
	this->setContentType("");
	this->setLastModified("");
}

Response::~Response(void)
{
}

//methods
std::string	Response::buildHeader(void)
{
	std::stringstream buffer;
	buffer	<< this->_statusLine->toString() << "\n"
			<< "Accept-Ranges: bytes\n"
			<< "Connection: close\n"
			<< "Content-Length: " << this->getContentLength() << "\n";
	if (!this->getContentType().empty()) { buffer << "Content-Type: " << this->getContentType() << "\n"; }
	if (!this->getLastModified().empty()) { buffer << "Last-Modified: " << this->getLastModified() << "\n"; }
	buffer << "Server: webserv\n";
	this->setHeader(buffer.str());
	return (buffer.str());
}

std::string	Response::buildResponse(void)
{
	std::stringstream buffer;

	buffer << this->getHeader() << "\n" << this->getBody();
	this->_str = buffer.str();
	this->setContentLength(this->toString().length());
	return (this->_str);
}

//getters & setters
void			Response::setContentType(std::string contentType)
{
	this->_contentType = contentType;
}

std::string		Response::getContentType(void)
{
	return (this->_contentType);
}

void			Response::setContentLength(int contentLength)
{
	this->_contentLength = contentLength;
}

int				Response::getContentLength(void)
{
	return (this->_contentLength);
}

void			Response::setLastModified(std::string lastModified)
{
	this->_lastModified = lastModified;
}

std::string		Response::getLastModified(void)
{
	return (this->_lastModified);
}

void			Response::setBody(std::string body)
{
	this->_body = body;
}

std::string		Response::getBody(void)
{
	return (this->_body);
}

void			Response::setHeader(std::string header)
{
	this->_header = header;
}

std::string			Response::getHeader(void)
{
	return (this->_header);
}

std::string		Response::toString(void)
{
	return (this->_str);
}

const char *Response::toCString(void)
{
	return (this->_str.c_str());
}

// Utils
std::string	getLastModifiedDate(std::string path)
{
	FILE*				file = std::fopen(path.c_str(), "rb");
	std::ostringstream	ss;
	if (file)
	{
		struct stat info;
		if (stat(path.c_str(), &info) == 0)
		{
			time_t	timestamp = info.st_mtime;
			struct tm* modTime = std::gmtime(&timestamp); 												// create a time structure (struct tm*);
			char formattedDate[64];																		// buffer to receive the formatted time structure
			std::strftime(formattedDate, sizeof(formattedDate), "%a, %d %b %Y %H:%M:%S GMT", modTime);	// print a formatted (struct tm*) structure containing time info;
			return (std::string(formattedDate));
		}
		else
		{
			ss << "(" << path << ") error getting file info"; std::cout << ss.str() << std::endl;
		}
		std::fclose(file);
	}
	else
	{
		ss.str(""); ss << "(" << path << ") open file failed"; std::cout << ss.str() << std::endl;
	}
	return ("");
}

std::string	getFileContentType(std::string path)
{
	std::size_t	dotPos = path.rfind('.');
	if (dotPos != std::string::npos)
	{
		std::string extension = path.substr(dotPos + 1);

		if (extension == "html" || extension == "html")
			return ("text/html");
		else if (extension == "css")
			return ("text/css");
		else if (extension == "js")
			return ("text/javascript");
		else if (extension == "xml")
			return ("text/xml");
		else if (extension == "txt")
			return ("text/plain");

		if (extension == "jpg" || extension == "jpeg")
			return ("image/jpeg");
		else if (extension == "png")
			return ("image/png");
		else if (extension == "gif")
			return ("image/gif");
		else if (extension == "bmp")
			return ("image/bmp");
		else if (extension == "svg")
			return ("image/svg+xml");

		if (extension == "pdf")
			return ("application/pdf");
		else if (extension == "doc" || extension == "docx")
			return ("application/msword");
		else if (extension == "xls" || extension == "xlsx")
			return ("application/vnd.ms-excel");
		else if (extension == "pptx" || extension == "ppt")
			return ("application/vnd.ms-powerpoint");
		else if (extension == "zip")
			return ("application/zip");

		if (extension == "ttf")
			return ("font/ttf");
		else if (extension == "woff")
			return ("font/woff");
		else if (extension == "woff2")
			return ("font/woff2");

		if (extension == "mpeg")
			return ("audio/mpeg");
		else if (extension == "wav")
			return ("audio/wav");
		else if (extension == "mp4")
			return ("video/mp4");
		else if (extension == "avi")
			return ("video/x-msvideo");
	}
	return ("application/octet-stream");
}
/*
image/[jpg,jpeg,png,ico,bmp,gif]
text/[html,css,javascript]
application/[pdf]
*/