#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <sstream>

#include <string>
#include <map>
#include <vector>

#include "SizetOrString.cpp"
#include "HTTPHeader.hpp"

#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
	int                      sfd, s;
	char                     buf[BUF_SIZE];
	ssize_t                  nread;
	socklen_t                peer_addrlen;
	struct addrinfo          hints;
	struct addrinfo          *result, *rp;
	struct sockaddr_storage  peer_addr;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* TCP socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	s = getaddrinfo(NULL, argv[1], &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
		Try each address until we successfully bind(2).
		If socket(2) (or bind(2)) fails, we (close the socket
		and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol);
		if (sfd == -1)
			continue;

		// Source - https://stackoverflow.com/a/24194999
		int enable = 1;
		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
			perror("setsockopt(SO_REUSEADDR) failed");

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;                  /* Success */
		
		//close(sfd);
	}

	freeaddrinfo(result);           /* No longer needed */

	if (rp == NULL) {               /* No address succeeded */
		fprintf(stderr, "Error: Could not bind\n");
		exit(EXIT_FAILURE);
	}

	/* Read datagrams and echo them back to sender. */

	listen(sfd, 5);

	std::cout << "Server started\n"
		<< "Listening on port " << argv[1] << " (socked fd = " << sfd << ") ..." << std::endl;
	/* the server routine */

	for (;;) {

		// accepting connection request
		peer_addrlen = sizeof(peer_addr);
		int clientSocket
			= accept(sfd, (struct sockaddr *) &peer_addr, &peer_addrlen);
		if (clientSocket < 0) {
			fprintf(stderr, "Error: accepting client connection!\n");
			exit(EXIT_FAILURE);
		}

		nread = recv(clientSocket, buf, sizeof(buf) - 1, 0);
		if (nread < 0)
		{
			fprintf(stderr, "Error: receiving message from client!\n");
			continue ;
		}

		/* parse buf and build HTTPRequest object */
		HTTPRequest_parse(buf, nread);
		

		/* based on the HTTPRequest.isValid() one can determine what to send back */
		/* in case of HTTPRequest errors */

		/* based on the HTTPRequest object, build the HTTPResponse object */
		/* here, use the ServerConfig object to verify if the request can be */
		/* honoured; if not, send back an appropriate error message */

		/* then, serialize the HTTPResponse object and send it to the client socket */

		buf[nread] = '\0';
		std::cout << "Message from client (raw HTTP request of max " << BUF_SIZE << " bytes):\n"
			<< "--------------------------------\n"
			<< buf
			<< "--------------------------------\n"
			<< std::endl;

		char response[] = "HTTP/1.0 404 Resource not found.\n" \
						  "Content-Type: text/plain\n" \
						  "\n" \
						  "Not Found\n";
		//nread = send(clientSocket, buf, strlen(buf), 0);
		nread = send(clientSocket, response, strlen(response), 0);
		if (nread < 0)
		{
			fprintf(stderr, "Error: sending message back to client!\n");
		}

		close(clientSocket);
	}
}

#include "HTTPHeader.hpp"

typedef struct s_HTTPRequest
{
	enum rlKey { METHOD, URL, VERSION };			// request line keys

	std::string							requestLineStr;	// 1st line in the header
	std::map<rlKey, SizetOrString>		requestLine;	// 1st line broken down into
														// 0 - method
														// 1 - URL
														// 2 - HTTP version
	
	std::map<s_HTTPHeaderKey::e_HeaderKey, SizetOrString>	headers;

	std::string				body;
	size_t					bodyLen;

	enum ParseStatus { BAD_REQUEST = -400, AWAITING_MORE_DATA = 0, COMPLETE = 1 };
	ParseStatus				parseStatus; /* -xxx - error: 3 digit HTTP status; 
											   0 - awaiting more data;
											   1 - complete */
}	t_HTTPRequest;


void	HTTPRequest_parse(char *raw, size_t len, t_HTTPRequest &hr)
{
	std::string			rawStr(raw, len);
	std::stringbuf		sb(rawStr);
	std::ostream		os(&sb);
	std::string			line;
	
	if (!len)
	{
		hr.parseStatus = t_HTTPRequest::AWAITING_MORE_DATA;
		return ;
	}

	oss.rdbuf(&sb);
	if (!hr.requestLineStr.size())
	{
		if (!std::getLine(oss, line))
		{
			hr.parseStatus = t_HTTPRequest::AWAITING_MORE_DATA;
			return ;
		}
		rh.requestLine = line;
		HTTPRequest_parse_requestLine(&rh);	// TO-DO
		if (hr.parseStatus < 0)			// request line was malformed?
			return ;
	}

	while (std::getLine(oss, line))
	{
		if (line.find(HEADER_BODY_SEPARATOR) != std::string::npos)
		{
			HTTPRequest_parse_addHeader(hr, line);
			if (hr.parseStatus == t_HTTPRequest::AWAITING_MORE_DATA)		// malformed header line?
				return ;
		}
		else
			break ;
	}

	// parsed all the headers and reached the header-body separator
	// copy rest of string byte by byte

	if (oss.str().empty() && hr.headers["Content-Length"].asSize_t() > 0)
	{
		hr.bodyLen = hr.headers["Content-Length"].asSize_t();
	}
}
