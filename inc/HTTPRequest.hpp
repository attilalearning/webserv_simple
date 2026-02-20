/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:34:38 by aistok            #+#    #+#             */
/*   Updated: 2026/02/19 22:08:42 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

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
	bool headers_completed;
	int headersRequiredCount;

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

	HTTPRequest(const char *raw, size_t len);

	int parse(const char *raw, size_t len);
	int removePortion(std::string &line, std::string portion);

	int parseRequestLine(std::string line);
	int parseMethod(std::string method);
	int parseURL(std::string url);
	int parseVersion(std::string version);
	int URLIsValid(std::string url);

	int parseHeaderLine(std::string line);
	int countHeaderIfRequired(s_HTTPHeaderKey::e_HeaderKey key);
	int headerKeyIsValid(std::string key);
	int headerValueIsValid(std::string value);
	int headerKeyAlreadyProcessed(s_HTTPHeaderKey::e_HeaderKey eKey);
	int headerKeyIsSecurityRisk(s_HTTPHeaderKey::e_HeaderKey eKey);

	bool ready();

//	friend std::ostream &operator<<(std::ostream &os, HTTPRequest &hr);

protected:

	/* ... */

private:

	/* ... */

};

std::ostream &operator<<(std::ostream &os, HTTPRequest &hr);

#endif // HTTPREQUEST_HPP
