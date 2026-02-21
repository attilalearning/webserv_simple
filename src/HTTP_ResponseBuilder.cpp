/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseBuilder.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:48:39 by aistok            #+#    #+#             */
/*   Updated: 2026/02/20 19:57:49 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPHeader.hpp"
#include "ResponseBuilder.hpp"

std::string ResponseBuilder::serverBasePath = std::string("./");

HTTPResponse ResponseBuilder::build(ServerConfig sc, HTTPRequest hReq)
{
	if (hReq.parseStatus == HTTPRequest::BAD_REQUEST)
		return (build(BAD_REQUEST, sc));

	if (hReq.parseStatus == HTTPRequest::INCOMPLETE)
	{
		// throw exception ?
	}

	size_t requestMethod = hReq.requestLine[HTTPRequest::METHOD].asSize_t();

	if (requestMethod == METHOD_GET)
	{
		return (build_response_for_GET(sc, hReq));
	}
	else if (requestMethod == METHOD_POST)
	{
		return (build_response_for_POST(sc, hReq));
	}
	else if (requestMethod == METHOD_DELETE)
	{
		return (build_response_for_DELETE(sc, hReq));
	}
}

HTTPResponse ResponseBuilder::build_response_for_GET(ServerConfig sc, HTTPRequest hReq)
{
	HTTPResponse hResp;

	std::string requestedUrl = hReq.requestLine[HTTPRequest::URL].asString();

	try
	{
		Location loc = locationGetBestMatch(sc, requestedUrl, host);
		/* this function should return the best location */
	}
	catch (std::exception e)
	{
		hResp.setStatus(HTTPStatus::NOT_FOUND);
		//need to somehow load a default error page from server
		//or from serverConfig if there is any for the server or for the location
		return (hReq);
	}

	if (! loc.methods has METHOD_GET)
	{
		// 403 forbidden
		return (hReq);
	}

	if (ResourceIsDir(sc, loc, requestedUrl))
	{
		if (!loc.autoindex)
		{
			// 403 forbidden
			return (hReq);
		}
		// read dir content of requestUrl
		//
		// if content not reachable because of permissions -> 403 forbidden
		//
		// add content to hResp.body, adjust hResp.bodyLen,
		// add required headers, ex. content-length (OR transfer-encoding)
		return (hReq);
	}
	else
	{
		// resource is a file
		//
		// read file content of requestUrl
		//
		// if content not reachable because of permissions -> 403 forbidden
		//
		// add content to hResp.body, adjust hResp.bodyLen,
		// add required headers, ex. content-length (and mime-type?)
		return (hReq);
	}
	
	/*
	 *	response is based on sc.path, sc.root, sc.index and autoindex
	 *		and requestedUrl
	 *
	 *	we have to go through all the locations in serverConfig and check if
	 *	the requestUrl starts with any of the sc.path's
	 *	the locations in the serverConfig need to be sorted from the longest to
	 *	the shortest, ex:
	 *		/home/pages/contact			1st loc entry
	 *		/home/companyDescription	2nd loc entry
	 *		/contactUs					3rd loc entry
	 *		/							4th loc entry
	 *	and we need to match the longest such path to then check properties in
	 *	ex. for requestedUrl = "/home/pages/contact/email-form" the 1st entry should be matched
	 *		for requestedUrl = "/contactUs/ITDepartment/teams" the 3rd entry should be matched
	 *
	 *	if there is a match, if the requestUrl is a directory && autoindex = off -> 403 forbidden
	 *														  && autoindex = on -> generate directory listing
	 *										      a file, open file and copy contents into the response body
	 *						if directory or file is not accessible (no permissions) -> 403 forbidden
	 * 
	 * 	if there is no match, check if autoindex is 'on' and if so, proceed with
	 *	obtaining the directory listing, generate a HTML as body for the response
	 *
	 *	if there is no match and autoindex = off, send 403 Forbidden
	 * 
	 */

	hResp.setStatus(HTTPStatus::OK);
}