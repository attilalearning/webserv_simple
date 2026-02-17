/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPStatus.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:39:13 by aistok            #+#    #+#             */
/*   Updated: 2026/02/16 21:58:25 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPStatus.hpp"

/* 1xx Informational */
const int HTTPStatus::CONTINUE = 100;

/* 2xx Success */
const int HTTPStatus::OK = 200;
const int HTTPStatus::CREATED = 201;
const int HTTPStatus::ACCEPTED = 202;
const int HTTPStatus::NO_CONTENT = 204;

/* 3xx Redirections */
const int HTTPStatus::MOVED_PERMANENTLY = 301;
const int HTTPStatus::FOUND = 302;
const int HTTPStatus::SEE_OTHER = 303;
const int HTTPStatus::NOT_MODIFIED = 304;

/* 4xx Client Errors */
const int HTTPStatus::BAD_REQUEST = 400;
const int HTTPStatus::UNAUTHORIZED = 401;
const int HTTPStatus::FORBIDDEN = 403;
const int HTTPStatus::NOT_FOUND = 404;
const int HTTPStatus::CONFLICT = 409;
const int HTTPStatus::UNPROCESSABLE_CONTENT = 422;

/* 5xx Server Errors */
const int HTTPStatus::INTERNAL_SERVER_ERROR = 500;
const int HTTPStatus::NOT_IMPLEMENTED = 501;
const int HTTPStatus::BAD_GATEWAY = 502;
const int HTTPStatus::SERVICE_UNAVAILABLE = 503;
const int HTTPStatus::GATEWAY_TIMEOUT = 504;

const char *HTTPStatus::message(int status)
{
	switch (status)
	{
	case CONTINUE:
		return "Continue";

	case OK:
		return "OK";
	case CREATED:
		return "Created";
	case ACCEPTED:
		return "Accepted";
	case NO_CONTENT:
		return "No Content";

	case MOVED_PERMANENTLY:
		return "Moved Permanently";
	case FOUND:
		return "Found";
	case SEE_OTHER:
		return "See Other";
	case NOT_MODIFIED:
		return "Not Modified";

	case BAD_REQUEST:
		return "Bad Request";
	case UNAUTHORIZED:
		return "Unauthorized";
	case FORBIDDEN:
		return "Forbidden";
	case NOT_FOUND:
		return "Not Found";
	case CONFLICT:
		return "Conflict";
	case UNPROCESSABLE_CONTENT:
		return "Unprocessable Content";

	case INTERNAL_SERVER_ERROR:
		return "Internal Server Error";
	case NOT_IMPLEMENTED:
		return "Not Implemented";
	case BAD_GATEWAY:
		return "Bad Gateway";
	case SERVICE_UNAVAILABLE:
		return "Service Unavailable";
	case GATEWAY_TIMEOUT:
		return "Gateway Timeout";

	default:
		return "Unknown Status";
	}
}
