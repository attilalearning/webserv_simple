/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:24:07 by aistok            #+#    #+#             */
/*   Updated: 2026/02/17 21:11:30 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

std::string toUpperCase(std::string &original)
{
	std::string upperCaseCopy = original;
	for (size_t i = 0; i < upperCaseCopy.length(); ++i)
	{
		upperCaseCopy[i] = static_cast<char>(std::toupper(
			static_cast<unsigned char>(upperCaseCopy[i])));
	}
	return (upperCaseCopy);
}

std::string &capitaliseFirstLetter(std::string &str)
{
	if (!str.empty())
	{
		unsigned char first = static_cast<unsigned char>(str[0]);
		str[0] = static_cast<char>(std::toupper(first));

		for (std::string::size_type i = 1; i < str.size(); ++i)
		{
			unsigned char c = static_cast<unsigned char>(str[i]);
			str[i] = static_cast<char>(std::tolower(c));
		}
	}
	return (str);
}

std::string &trimString(std::string &str, std::string stripChars)
{
	std::string::size_type start = 0;
	std::string::size_type end = str.size();

	if (end > 0)
	{
		while (start < end &&
			   (stripChars.find(str[start]) != std::string::npos))
			++start;

		while (end > start &&
			   (stripChars.find(str[end - 1]) != std::string::npos))
			--end;

		if (start != 0 || end != str.size())
			str = str.substr(start, end - start);
	}
	return (str);
}
