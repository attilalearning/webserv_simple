/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPStatus.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:37:18 by aistok            #+#    #+#             */
/*   Updated: 2026/02/16 21:55:19 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSTATUS_HPP
#define HTTPSTATUS_HPP

struct HTTPStatus
{
	/* 1xx Informational */
	static const int CONTINUE;

	/* 2xx Success */
	static const int OK;
	static const int CREATED;
	static const int ACCEPTED;
	static const int NO_CONTENT;

	/* 3xx Redirections */
	static const int MOVED_PERMANENTLY;
	static const int FOUND;
	static const int SEE_OTHER;
	static const int NOT_MODIFIED;

	/* 4xx Client Errors */
	static const int BAD_REQUEST;
	static const int UNAUTHORIZED;
	static const int FORBIDDEN;
	static const int NOT_FOUND;
	static const int CONFLICT;
	static const int UNPROCESSABLE_CONTENT;

	/* 5xx Server Errors */
	static const int INTERNAL_SERVER_ERROR;
	static const int NOT_IMPLEMENTED;
	static const int BAD_GATEWAY;
	static const int SERVICE_UNAVAILABLE;
	static const int GATEWAY_TIMEOUT;

	static const char *message(int status);
};

#endif // HTTPSTATUS_HPP
