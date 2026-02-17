/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPHeader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:39:13 by aistok            #+#    #+#             */
/*   Updated: 2026/02/17 14:05:09 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPHeader.hpp"

const char *s_HTTPHeaderKey::toString(s_HTTPHeaderKey::e_HeaderKey HeaderKey)
{
	switch (HeaderKey)
	{
	case HOST:
		return ("Host");
	case CONTENT_LENGTH:
		return ("Content-Length");
	case TRANSFER_ENCODING:
		return ("Transfer-Encoding");
	case CONTENT_TYPE:
		return ("Content-Type");
	case RANGE:
		return ("Range");
	case USER_AGENT:
		return ("User-Agent");
	case CONNECTION:
		return ("Connection");
	case DATE:
		return ("Date");
	case CONTENT_RANGE:
		return ("Content-Range");

	default:
		return ("Unknown-HeaderKey");
	}
}

const s_HTTPHeaderKey::e_HeaderKey s_HTTPHeaderKey::toEnum(std::string HeaderKeyStr)
{
	if (HeaderKeyStr == "Host")
		return (HOST);
	if (HeaderKeyStr == "Content-Length")
		return (CONTENT_LENGTH);
	if (HeaderKeyStr == "Transfer-Encoding")
		return (TRANSFER_ENCODING);
	if (HeaderKeyStr == "Content-Type")
		return (CONTENT_TYPE);
	if (HeaderKeyStr == "Range")
		return (RANGE);
	if (HeaderKeyStr == "User-Agent")
		return (USER_AGENT);
	if (HeaderKeyStr == "Connection")
		return (CONNECTION);
	if (HeaderKeyStr == "Date")
		return (DATE);
	if (HeaderKeyStr == "Content-Range")
		return (CONTENT_RANGE);
	return (UNKNOWN_HEADERKEY);
}
