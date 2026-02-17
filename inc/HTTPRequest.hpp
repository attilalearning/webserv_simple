/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:34:38 by aistok            #+#    #+#             */
/*   Updated: 2026/02/17 22:05:30 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>

#include "SizetOrString.hpp"
#include "Utils.hpp"
#include "HTTPHeader.hpp"

// TO-DO: orthodox canonical form!

class HTTPRequest
{
public:

	/* request line keys */
	enum rlKey
	{
		METHOD,
		URL,
		VERSION
	};

	/* 1st line in request headers */ // TO-DO: make this private?
	std::string requestLineStr;

	/* 1st line broken down into: METHOD, URL, VERSION (http version) */
	std::map<rlKey, SizetOrString> requestLine;
	bool requestLine_completed;

	std::map<s_HTTPHeaderKey::e_HeaderKey, SizetOrString> headers;
	int headersRequiredCount;
	bool headers_completed;

	size_t bodyLen;
	std::string body;
	bool body_completed;

	enum ParseStatus
	{
		BAD_REQUEST = -400,
		INCOMPLETE = 0,
		COMPLETE = 1
	};

	ParseStatus parseStatus;

	HTTPRequest(char *raw, size_t len);

	int parse(char *raw, size_t len);
	int removePortion(std::string &line, std::string portion);
	int parseRequestLine(std::string line);
	int parseMethod(std::string method);
	int parseURL(std::string url);
	int parseVersion(std::string version);
	int URLIsValid(std::string url);

	int parseHeaderLine(std::string line);
	int headerKeyIsValid(std::string key);
	int headerValueIsValid(std::string value);
	int headerKeyAlreadyProcessed(s_HTTPHeaderKey::e_HeaderKey eKey);
	int headerKeyIsSecurityRisk(s_HTTPHeaderKey::e_HeaderKey eKey);

	bool ready();

protected:

	/* ... */

private:

	/* ... */

};
