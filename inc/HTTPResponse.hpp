/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:34:38 by aistok            #+#    #+#             */
/*   Updated: 2026/02/20 14:32:06 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <iostream>
#include <map>

#include "SizetOrString.hpp"
#include "Utils.hpp"
#include "HTTPHeader.hpp"

// TO-DO: orthodox canonical form!

class HTTPResponse
{
public:

	/* response line keys */
	enum rlKey
	{
		STATUS,
		MESSAGE,
		VERSION
	};

	/* 1st line broken down into: METHOD, URL, VERSION (http version) */
	std::map<rlKey, SizetOrString> responseLine;
	bool responseLine_completed;

	std::map<s_HTTPHeaderKey::e_HeaderKey, SizetOrString> headers;
	bool headers_completed;
	int headersRequiredCount;

	size_t bodyLen;
	std::string body;
	bool body_completed;

	HTTPResponse();
	HTTPResponse(HTTPStatus status);

	setStatus(); /* will set status message too */
	//add headers
	//add body / encode body, including:
		// add required headers (ex content length, transfer encoding, range? mime type?)

	toString();

	bool ready(); // ?

protected:

	/* ... */

private:

	/* ... */

};

std::ostream &operator<<(std::ostream &os, HTTPResponse &hResp);

#endif // HTTPRESPONSE_HPP
