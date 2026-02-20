/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseBuilder.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:48:39 by aistok            #+#    #+#             */
/*   Updated: 2026/02/20 11:29:48 by aistok           ###   ########.fr       */
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
	HTTPResponse build(ServerConfig sc, HTTPRequest hReq);
};

#endif // RESPONSEBUILDER_HPP
