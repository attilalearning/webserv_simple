/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:40:39 by aistok            #+#    #+#             */
/*   Updated: 2026/02/19 20:11:51 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp_test.hpp"

std::string readContent(const std::string filename)
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
	{
		throw std::runtime_error(
			std::string("Failed to open file: ") + filename + "\n");
	}

	std::string content;
	std::string line;
	while (getline(file, line))
	{
		content += line;
		content += "\n";
	}

	file.close();

	return (content);
}
