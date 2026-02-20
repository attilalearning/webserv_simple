/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPHeader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:37:18 by aistok            #+#    #+#             */
/*   Updated: 2026/02/19 21:25:25 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHEADER_HPP
#define HTTPHEADER_HPP

#include <string>

#define CR "\r"
#define LF "\n"
#define CRLF CR LF
#define DISALLOWED_CHARS_IN_FIELD_VALUE " \t"
#define ALLOWED_CHARS_IN_FIELD_NAME "!#$%&'*+-.^_`|~"
#define SUCCESS 1
#define FAILURE 0

/*
 * Minimal set of headers in a request
 * (sent by the client to the server):
 *
 * 	GET / HTTP/1.1		request line !
 *	Host				required in HTTP/1.1
 *	Content-Length		only if the request has a body
 *	Transfer-Encoding	chunked
 *						NOTES:
 * 						appears, when the client is sending data to the
 *						server, and it does not know the length of the
 *						content up front (ex: streaming video or audio);
 *						IMPORTANT: this may be a security vulnerability
 *						if it appears beside Content-Length! In this case,
 *						the request is rejected!
 *						https://portswigger.net/web-security/request-smuggling
 *
 *	Content-Type		only if the request has a body (e.g. POST/PUT)
 *
 *	User-Agent			optional (very common, not required)
 *	Accept				optional
 *	Range				optional (only when requesting partial content)
 *	Connection			optional (e.g. keep-alive, close)
 */

/*
 * Minimal set of headers in a response
 * (sent by the server to the client):
 *
 * 	HTTP/1.1 200 OK		status line (or response line)
 *	Date				yes, response header (SHOULD be sent by origin servers)
 *
 *	Content-Type		if the response has a body
 *	Content-Length		if the response has a body AND IS NOT CHUNKED !
 *	Transfer-Encoding	appears, when the server is sending data to the
 *						client, and it does not know the length upfront;
 *						IMPORTANT SECURITY RISK, see above!
 *
 *	Content-Range		when returning partial content, sample value:
 *						bytes 0-99/1234
 *	Connection			optional (often mirrors request intent)
 */

typedef struct s_HTTPHeaderKey
{
	enum e_HeaderKey {

		UNKNOWN_HEADERKEY,

		/* Used in Request & Response headers */
		
		CONTENT_LENGTH,
		TRANSFER_ENCODING,
		CONTENT_TYPE,

		/* Used only in request headers */

		HOST,
		RANGE,

		USER_AGENT,
		CONNECTION,

		/* Used only in response headers */

		DATE,
		CONTENT_RANGE
	};

	static const char *toString(e_HeaderKey HeaderKey);
	static e_HeaderKey toEnum(std::string HeaderKeyStr);
}	t_HTTPHeaderKey;

enum e_HTTPMethods
{
	METHOD_GET,
	METHOD_POST,
	METHOD_DELETE
};

#endif // HTTPHEADER_HPP
