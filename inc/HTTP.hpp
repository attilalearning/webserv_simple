/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 21:56:26 by aistok            #+#    #+#             */
/*   Updated: 2026/02/21 01:09:46 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_HPP
#define HTTP_HPP

#include "HTTP_Defines.hpp"
#include "HTTP_Status.hpp"
#include "HTTP_Method.hpp"
#include "HTTP_FieldName.hpp"
#include "HTTP_Request.hpp"
// #include "Response.hpp"
// #include "ResponseBuilder.hpp"

class HTTP
{
public:
	typedef HTTP_Status Status;
	typedef HTTP_Method Method;
	typedef HTTP_FieldName FieldName;
	typedef HTTP_Request Request;
	/*
	typedef HTTPResponse Response;
	typedef HTTPResponseBuilder ResponseBuilder;
	*/
};

#endif // HTTP_HPP
