#include "OperateRequest.hpp"

OperateRequest::OperateRequest(void) {}

OperateRequest::~OperateRequest(void) {}

//getter
std::string	&OperateRequest::getStartLine(void) {
	return (startLine_);
}
std::string	&OperateRequest::getHeaders(void) {
	return (headers_);
}

//setter

void	OperateRequest::checkRequestMessage(Connection *c) {

	if (c->getPhaseMsg() == START_LINE_INCOMPLETE)
	{
		size_t pos;
		if ((pos = c->getBuffer().find(CRLF))!= std::string::npos)
			c->setPhaseMsg(START_LINE_COMPLETE);
	}
	if (c->getPhaseMsg() == START_LINE_COMPLETE)
	{
		//parse start line
		std::cout << "Parse Start Line" << std::endl;
		parseStartLine(c);
		// if ((pos = c->getBuffer().find(CRLFCRLF)) == std::string::npos)
		// 	c->setPhaseMsg(HEADER_INCOMPLETE);
	}
	if (c->getPhaseMsg() == HEADER_INCOMPLETE)
	{
		size_t pos1;
		if ((pos1 = c->getBuffer().find(CRLFCRLF)) != std::string::npos)
			c->setPhaseMsg(HEADER_COMPLETE);
	}
	if (c->getPhaseMsg() == HEADER_COMPLETE)
	{
		std::cout << "Parse Header" << std::endl;
		// headers_ = c->getBuffer().substr(tmp_, c->getBuffer().length());
		// headers_ = c->getBuffer().substr(0, pos + LEN_CRLFCRLF);
		// c->getBuffer().erase(0, pos + LEN_CRLFCRLF);
		// tmp_ = pos + LEN_CRLFCRLF;
	// 	// std::cout << "header: " << headers_ << std::endl;
	// 	// std::cout << "tmp_: " << tmp_ << std::endl;
		//parse header
		parseHeaders(c);
	// 	std::cout << "Header parse done" << std::endl;
	// 	std::cout << "buffer check: " << c->getBuffer() << std::endl;
		checkHeader(c);
	}
}

void	OperateRequest::parseStartLine(Connection *c) {

	size_t pos = c->getBuffer().find(CRLF);
	startLine_ = c->getBuffer().substr(0, pos);
	c->getBuffer().erase(0, pos + LEN_CRLF);
	//method check : GET/POST/DELETE -> toupper / if not Error 400
	std::vector<std::string> split_start_line = splitDelim(startLine_, " ");
	if (split_start_line.size() != 3)
	{
		c->setReqStatusCode(BAD_REQUEST);
		c->setPhaseMsg(HEADER_COMPLETE);
		std::cout << "start line argument wrong request code : " <<  c->getReqStatusCode() <<  std::endl;
		return ;
	}
	// for (size_t i = 0; i < split_start_line.size(); i++)
	// 	std::cout << split_start_line[i] << std::endl;
	// std::string method = startLine_.substr(0, startLine_.find_first_of(" "));
	// std::cout << method << std::endl;
	if (!checkMethod(split_start_line[0]))
	{
		c->setReqStatusCode(BAD_REQUEST);
		c->setPhaseMsg(HEADER_COMPLETE);
		return ;
	}
	else
		c->getRequest().setMethod(split_start_line[0]);

	//path check:
	c->getRequest().setPath(split_start_line[1]);

	//HTTP/1.1 check: 'HTTP/' '1.*' / if not Error 400/505
	std::string http = split_start_line[2].substr(0, 5);
	std::string version = split_start_line[2].substr(5, split_start_line[2].length());
	int cmp = http.compare("HTTP/");
	if (!checkVersion(version) || version.length() != 3 || cmp)
	{
		c->setReqStatusCode(BAD_REQUEST);
		c->setPhaseMsg(HEADER_COMPLETE);
		return ;
	}
	cmp = version.compare(0, 2, "1.");
	if (cmp)
	{
		c->setReqStatusCode(HTTP_VERSION_NOT_SUPPORTED);
		c->setPhaseMsg(HEADER_COMPLETE);
		return ;
	}
	c->getRequest().setVersion(http + version);
	c->setPhaseMsg(HEADER_INCOMPLETE);
}

void	OperateRequest::parseHeaders(Connection *c) {

	size_t pos = c->getBuffer().find(CRLFCRLF);
	headers_ = c->getBuffer().substr(0, pos + LEN_CRLF);
	c->getBuffer().erase(0, pos + LEN_CRLFCRLF);
	std::cout << "headers" << std::endl;
	std::cout << headers_ << std::endl;
	// size_t header_len = header.length();
	size_t pos1 = 0;
	int code = 0;
	int i = 0;
	while ((pos1 = headers_.find(CRLF)) != std::string::npos)
	{
		std::string headerline = "";
		headerline = headers_.substr(0, pos1);
		std::cout << "Header line " << i++ << " : " << headerline << std::endl;
		// }

		//headerline parse - argument is < 2 => 400 // if field name is not alpha => 400
													// if there's sth between fild name and colon => 400
		if (headers_.length() == 2)
			break ;
		if ((code = parseHeaderLine(c, headerline)) != NOT_DEFINE)
		{
			c->setReqStatusCode(code);
			c->setPhaseMsg(HEADER_COMPLETE);
			return ;
		}
		headers_ = headers_.substr(pos1 + LEN_CRLF, headers_.length());
		// std::cout << "headers to parse line : " << std::endl;
		std::cout << headers_ << std::endl;
		// std::cout << "header 길이: " << headers_.length() << std::endl;
	}
	// std::cout <<
}

int		OperateRequest::parseHeaderLine(Connection *c, std::string headerline) {
	std::vector<std::string> header_line_parse = splitDelim(headerline, ": ");
	if (header_line_parse.size() != 2)
	{
		// header_line_parse = splitDelim(headerline, ":");
		// if (header_line_parse.size() != 2)
		std::cout << header_line_parse.size() << std::endl;
		std::cout<< "/////////////////////////////////////////////" << std::endl;
			return (BAD_REQUEST);
	}
	// std::vector<std::string> key_parse = splitDelim(header_line_parse[0], ":");

	// std::string key = key_parse[0];
	std::string key = header_line_parse[0];
	std::string value = header_line_parse[1];
	std::cout << "header key: " << key << std::endl;
	std::cout << "header value: " << value << std::endl;
	c->getRequest().setHeader(key, value);
	return (NOT_DEFINE);
}

/* Set and check details along with header key and method of request message */
void	OperateRequest::checkHeader(Connection *c) {
	if (c->getReqStatusCode() != NOT_DEFINE)
	{
		c->setPhaseMsg(BODY_COMPLETE);
		return ;
	}

	//get Client_Max_Body_Size
	c->client_max_body_size = c->getBlock().getClientMaxBodySize();

	if ((c->getRequest().getRequestHeaders().count("Content-Length")))
	{
		c->content_length = fromString<int>((c->getRequest().getHeaderValue("Content-Length")));
		// std::cout << "content-length in function:" << c->content_length << std::endl;
		if (c->content_length > (c->client_max_body_size))
		{
			c->setReqStatusCode(PAYLOAD_TOO_LARGE);
			c->setPhaseMsg(BODY_COMPLETE);
			return ;
		}
		if (!(c->getBuffer().empty())) 	//put the rest of buffer into request body member
		{
			body_ = c->getBuffer().substr(0, c->getBuffer().length());
			std::cout << "body check: " << body_ << std::endl;
			c->getBuffer().erase(0, c->getBuffer().length());
			c->getRequest().setBody(body_);
		}
	}

	if (!c->getRequest().getRequestHeaders().count("Host"))
	{
		c->setReqStatusCode(BAD_REQUEST);
		c->setPhaseMsg(BODY_COMPLETE);
		return ;
	}


	//GET

	//POST

	//DELETE

	//
}


//utiles
std::vector<std::string> OperateRequest::splitDelim(std::string s, std::string delim) {
    size_t pos_start = 0, pos_end, delim_len = delim.length();
    std::string 		token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delim, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

int		OperateRequest::checkMethod(const std::string &s) {

	for(size_t i = 0; i < s.length(); i++)
	{
		char c = s[i];
		if (!isupper(c) || !isalpha(c))
			return (false);
	}
	return (true);
}

int			OperateRequest::checkVersion(const std::string &s) {
	for (size_t i = 0; i < s.length(); i++)
	{
		char c = s[i];
		if (isdigit(c) || (c == '.'))
			i++;
		else
			return (false);
	}
	return (true);
}

int			OperateRequest::checkHeaderKey(const std::string &s) {
	for (size_t i = 0; i < s.length(); i++)
	{
		char c = s[i];
		if (isalpha(c) || (c == '_'))
			i++;
		else
			return (false);
	}
	return (true);
}

std::string	OperateRequest::trimWhiteSpace(std::string &s) {

	std::string str;
	std::string whitespace(" \n\r\t\f\v");
	size_t found1 = s.find_first_not_of(whitespace);
	size_t found2 = s.find_last_not_of(whitespace);
	str = s.substr(found1, found2 - found1 + 1);
	return (str);
}

int Stoi(const std::string &str, size_t *idx, int base) {
  char *end;
  const char *p = str.c_str();
  long num = std::strtol(p, &end, base);
  if (p == end) {
    throw std::invalid_argument("Stoi");
  }
  if (num < std::numeric_limits<int>::min() ||
      num > std::numeric_limits<int>::max() || errno == ERANGE) {
    throw std::out_of_range("Stoi");
  }
  if (idx != NULL) {
    *idx = static_cast<size_t>(end - p);
  }
  return static_cast<int>(num);
}
