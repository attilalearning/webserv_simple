/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:46:32 by aistok            #+#    #+#             */
/*   Updated: 2026/02/20 09:48:32 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream> // stringbuf
#include <istream> // istream

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(const char *raw, size_t len) : requestLine_completed(false),
												  headers_completed(false),
												  headersRequiredCount(0),
												  bodyLen(0),
												  body_completed(false)
{
	parse(raw, len);
}

/* getline removes the '\n' from each line it reads! */
int HTTPRequest::parse(const char *raw, size_t len)
{
	if (!len)
	{
		parseStatus = HTTPRequest::INCOMPLETE;
		return (FAILURE);
	}

	std::string rawStr(raw, len);
	std::stringbuf sb(rawStr);
	std::istream is(&sb);
	std::string line;

	if (!requestLine_completed)
	{
		if (!std::getline(is, line))
		{
			/* no data available
			 * QUESTION: is this even possible? for '\n' to be missing?
			 */
			this->parseStatus = HTTPRequest::INCOMPLETE;
			return (FAILURE);
		}
		if (!parseRequestLine(line))
			/* request line was malformed?
			 * parseStatus will be set!
			 */
			return (FAILURE);
		requestLine_completed = true;
	}

	while (!headers_completed && std::getline(is, line))
	{
		if (line == CR) /* LF was removed by getline! */
		{
			/* reached the end of headers;
			 * body may be present after this
			 */
			if (headersRequiredCount < 2)
			{
				parseStatus = HTTPRequest::BAD_REQUEST;
				return (FAILURE);
			}
			headers_completed = true;
			break;
		}
		else
		{
			if (!HTTPRequest::parseHeaderLine(line))
				/* malformed header line
				 * TO-DO: or awaiting for more data?
				 * parseStatus is now set accordingly!
				 */
				return (FAILURE);
		}
	}

	/*	by now, we parsed all the headers and reached the header-body separator
	 *	(line == CRLF) is true!
	 *	if there is a body present in the request,
	 *	copy rest of string byte by byte into the body
	 */

	/*	TO-DO: this last bit may need more work, in case there is
	 *	more data to read (for ex, in chunks?)
	 */
	if (!is.eof())
	{
		if (headers.find(s_HTTPHeaderKey::CONTENT_LENGTH) != headers.end() &&
			headers[s_HTTPHeaderKey::CONTENT_LENGTH].asSize_t() > 0)
			bodyLen = headers[s_HTTPHeaderKey::CONTENT_LENGTH].asSize_t();
		else if (headers.find(s_HTTPHeaderKey::TRANSFER_ENCODING) != headers.end())
			bodyLen = is.rdbuf()->in_avail();

		bodyLen = is.rdbuf()->in_avail();
		this->body = std::string(bodyLen, '\0');
		is.read(&this->body[0], bodyLen);

		if (is.gcount() != static_cast<std::streamsize>(bodyLen))
		{
			parseStatus = HTTPRequest::INCOMPLETE;
			return (FAILURE); /* TO-DO: should this be SUCCESS?
							   * ex: if it's "Transfer-Encoding: chunked
							   */
		}
	}
	
	body_completed = true;
	parseStatus = HTTPRequest::COMPLETE;
	return (SUCCESS);
}

/* TO-DO: if this function is used elsewhere too, place it in utils */
int HTTPRequest::removePortion(std::string &line, std::string portion)
{
	if (line.find(portion) == std::string::npos)
		return (FAILURE);
	line.erase(line.size() - portion.size(), portion.size());
	return (SUCCESS);
}

// TO-DO: should be protected
int HTTPRequest::parseRequestLine(std::string line)
{
	/*
	 *	getline removes '\n' (LF), so,
	 *	only check and remove '\r' (CR).
	 */
	if (!removePortion(line, CR))
	{
		parseStatus = HTTPRequest::BAD_REQUEST;
		return (FAILURE);
	}

	int part = 1;
	std::string::size_type start = 0;
	std::string::size_type end = 0;

	std::string subString;
	while ((end = line.find(" ", start)) != std::string::npos &&
		   part < 3)
	{
		subString = line.substr(start, end - start);
		start = end + 1;
		if (part == 1)
		{
			if (!parseMethod(subString))
			{
				parseStatus = HTTPRequest::BAD_REQUEST;
				return (FAILURE);
			}
		}
		else if (part == 2)
		{
			if (!parseURL(subString))
			{
				parseStatus = HTTPRequest::BAD_REQUEST;
				return (FAILURE);
			}
		}
		part++;
	}

	if (part == 3)
	{
		subString = line.substr(start, line.size() - start);
		if (!parseVersion(subString))
		{
			parseStatus = HTTPRequest::BAD_REQUEST;
			return (FAILURE);
		}
	}
	else
	{
		parseStatus = HTTPRequest::BAD_REQUEST;
		return (FAILURE);
	}

	/*	request line parsed succesfully
	 *	this line is mandatory to be present in the request,
	 *	therefore, count it in the required headers
	 */
	headersRequiredCount++;
	return (SUCCESS);
}

int HTTPRequest::parseMethod(std::string method)
{
	if (method == "GET")
		requestLine[HTTPRequest::METHOD] = SizetOrString(METHOD_GET);
	else if (method == "POST")
		requestLine[HTTPRequest::METHOD] = SizetOrString(METHOD_POST);
	else if (method == "DELETE")
		requestLine[HTTPRequest::METHOD] = SizetOrString(METHOD_DELETE);
	else
		return (FAILURE);
	return (SUCCESS);
}

int HTTPRequest::parseURL(std::string url)
{
	if (!URLIsValid(url))
		return (FAILURE);
	requestLine[HTTPRequest::URL] = SizetOrString(url);
	return (SUCCESS);
}

int HTTPRequest::parseVersion(std::string version)
{
	if (version == "HTTP/1.1")
		requestLine[HTTPRequest::VERSION] = SizetOrString(11);
	else if (version == "HTTP/1.0")
		requestLine[HTTPRequest::VERSION] = SizetOrString(10);
	else
		return (FAILURE);
	return (SUCCESS);
}

int HTTPRequest::URLIsValid(std::string url)
{
	/* TO-DO: verify if url is valid */
	/* 	ex. contains white spaces, control characters,
	 *	etc. (RFC 9110, 9112, 3986) */
	(void) url;
	return (SUCCESS);
}

// TO-DO: should be protected
int HTTPRequest::parseHeaderLine(std::string line)
{
	/*
	 *	getline removes '\n' (LF), so,
	 *	only check and remove '\r' (CR).
	 */
	if (!removePortion(line, CR))
	{
		parseStatus = HTTPRequest::BAD_REQUEST;
		return (FAILURE);
	}

	std::string::size_type pos = line.find(":", 0);
	if (pos == std::string::npos)
	{
		parseStatus = HTTPRequest::BAD_REQUEST;
		return (FAILURE);
	}

	std::string key = line.substr(0, pos);
	s_HTTPHeaderKey::e_HeaderKey key_enum = s_HTTPHeaderKey::toEnum(key); /* TO-DO: allow case insensitive comparison */
	std::string value = line.substr(pos + 1, line.size());
	if (key_enum == s_HTTPHeaderKey::UNKNOWN_HEADERKEY ||
		//! headerKeyIsValid(key) || //no longer needed as handled by key_enum = s_HTTPHeaderKey::toEnum(key);
		!headerValueIsValid(value) ||
		headerKeyAlreadyProcessed(key_enum) ||
		headerKeyIsSecurityRisk(key_enum))
	{
		parseStatus = HTTPRequest::BAD_REQUEST;
		return (FAILURE);
	}

	if (key_enum == s_HTTPHeaderKey::CONTENT_LENGTH)
	{
		size_t value_size_t;

		/* TO-DO: check for negative values? */
		if (toNumber(value, value_size_t))
			headers[key_enum] = SizetOrString(value_size_t);
		else
		{
			/* not possible to parse value as a number */
			parseStatus = HTTPRequest::BAD_REQUEST;
			return (FAILURE);
		}
	}
	else
	{
		value = trimString(value, DISALLOWED_CHARS_IN_FIELD_VALUE);
		headers[key_enum] = SizetOrString(value);
	}

	countHeaderIfRequired(key_enum);

	return (SUCCESS);
}

/* this function can include other headers
 * in the future if needed
 */
int HTTPRequest::countHeaderIfRequired(s_HTTPHeaderKey::e_HeaderKey key)
{
	if (key == s_HTTPHeaderKey::HOST)
		headersRequiredCount++;
	return (SUCCESS);
}

/* Defined in RFC 9112, summarized in RFC 9110 */
int HTTPRequest::headerKeyIsValid(std::string key)
{
	const static std::string allowedChars(ALLOWED_CHARS_IN_FIELD_NAME);

	if (key.empty())
		return (FAILURE);

	for (std::string::size_type i = 0; i < key.size(); ++i)
	{
		unsigned char c = static_cast<unsigned char>(key[i]);

		if (std::isalnum(c))
			continue;

		if (allowedChars.find(c, 0) == std::string::npos)
			return (FAILURE);
	}
	return (SUCCESS);
}

/* defined in RFC 9112, with semantics summarized in RFC 9110 */
int HTTPRequest::headerValueIsValid(std::string value)
{
	for (std::string::size_type i = 0; i < value.size(); ++i)
	{
		unsigned char c = static_cast<unsigned char>(value[i]);

		/* IMPORTANT SECURITY CONCERN:
		 * the below has CR and LF and '\t' characters covered!
		 */
		if (c < 32 || c == 127)
			return (FAILURE);
	}
	return (SUCCESS);
}

int HTTPRequest::headerKeyAlreadyProcessed(s_HTTPHeaderKey::e_HeaderKey eKey)
{
	if (headers.find(eKey) != headers.end())
		return (SUCCESS);
	return (FAILURE);
}

/* Disallow CONTENT_LENGTH && TRANSFER_ENCODING headers,
 * both at the same time in the http request to avoid "request smuggling"
 */
int HTTPRequest::headerKeyIsSecurityRisk(s_HTTPHeaderKey::e_HeaderKey eKey)
{
	if (eKey == s_HTTPHeaderKey::TRANSFER_ENCODING &&
		headerKeyAlreadyProcessed(s_HTTPHeaderKey::CONTENT_LENGTH))
		return (SUCCESS);

	if (eKey == s_HTTPHeaderKey::CONTENT_LENGTH &&
		headerKeyAlreadyProcessed(s_HTTPHeaderKey::TRANSFER_ENCODING))
		return (SUCCESS);

	return (FAILURE);
}

bool HTTPRequest::ready()
{
	return (this->parseStatus == HTTPRequest::COMPLETE ||
			this->parseStatus == HTTPRequest::BAD_REQUEST);
}

std::ostream &operator<<(std::ostream &os, HTTPRequest &hr)
{
	if (!hr.requestLine_completed) /* TO-DO: this is for debug only! */
	{
		os << "HTTP Request is INCOMPLETE!";
		return (os);
	}

	size_t method = hr.requestLine[HTTPRequest::METHOD].asSize_t();
	switch (method)
	{
	case METHOD_GET:
		os << "GET"; break;
	case METHOD_POST:
		os << "POST"; break;
	case METHOD_DELETE:
		os << "DELETE"; break;

	default:
		os << "UNKNOWN_METHOD";
	}

	os << " " << hr.requestLine[HTTPRequest::URL].asString() << " ";

	size_t version = hr.requestLine[HTTPRequest::VERSION].asSize_t();
	switch (version)
	{
	case 10:
		os << "HTTP/1.0"; break;
	case 11:
		os << "HTTP/1.1"; break;

	default:
		os << "UNKNOWN_METHOD";
	}

	os << CRLF;

	if (!hr.headers_completed) /* TO-DO: this is for debug only! */
	{
		os << "HTTP Request is INCOMPLETE!";
		return (os);
	}

	std::map<s_HTTPHeaderKey::e_HeaderKey, SizetOrString>::const_iterator it;
	for (it = hr.headers.begin(); it != hr.headers.end(); ++it)
	{
		s_HTTPHeaderKey::e_HeaderKey eKey = it->first;
		SizetOrString ssValue = it->second;

		os << s_HTTPHeaderKey::toString(eKey) << ": ";
		if (ssValue.type() == SizetOrString::SIZET)
			os << ssValue.asSize_t();
		else if (ssValue.type() == SizetOrString::STRING)
			os << ssValue.asString();

		os << CRLF;
	}

	os << CRLF;

	if (!hr.body_completed) /* TO-DO: this is for debug only! */
	{
		os << "HTTP Request is INCOMPLETE!";
		return (os);
	}

	os.write(hr.body.c_str(), hr.body.size());
	return (os);
}
