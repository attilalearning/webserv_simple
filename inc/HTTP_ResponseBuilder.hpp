/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseBuilder.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:48:39 by aistok            #+#    #+#             */
/*   Updated: 2026/02/20 19:53:08 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEBUILDER_HPP
#define RESPONSEBUILDER_HPP

#include "ConfigStructs.hpp"
#include "HTTPStatus.hpp"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

/*	this class should not be instantiable
 *	and should only contain static methods
 *
 *	TO-DO: orthodox canonical form
 */
class ResponseBuilder
{
public:
	/*
	 *	This is temporary, can be moved later to other struct or class
	 *
	 *	if webserv is given a config file as argument,
	 *	this variable will be overwritten by the the path to that config file
	 *
	 *	if no argument is present, this path will be the dafault,
	 *	where the WebServ will try to look for a config file.
	 *	
	 */
	static std::string serverBasePath;

	HTTPResponse build(ServerConfig sc, HTTPRequest hReq);
};

#endif // RESPONSEBUILDER_HPP
