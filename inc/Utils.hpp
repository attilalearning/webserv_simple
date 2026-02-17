/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:56:58 by mosokina          #+#    #+#             */
/*   Updated: 2026/02/17 21:18:42 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <sstream>
#include <string>

template <typename T>
std::string toString(const T &value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template <typename T>
bool toNumber(const std::string &str, T &out)
{
	std::istringstream iss(str);
	iss >> out;

	return !iss.fail() && iss.eof();
}

std::string toUpperCase(std::string &str);
std::string &capitaliseFirstLetter(std::string &str);
std::string &trimString(std::string &str, std::string stripChars);

#endif
