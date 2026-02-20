/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SizetOrString.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 07:10:34 by aistok            #+#    #+#             */
/*   Updated: 2026/02/19 21:17:54 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIZETORSTRING_HPP
#define SIZETORSTRING_HPP

#include <iostream>

class SizetOrString
{
public:
	enum Type
	{
		NONE,
		SIZET,
		STRING
	};

	SizetOrString();
	SizetOrString(size_t value);
	SizetOrString(const std::string &value);
	SizetOrString(const char *value);

	Type type() const;

	size_t asSize_t() const;
	const std::string &asString() const;

protected:
	/* ... */

private:
	Type _type;
	size_t _st;
	std::string _s;
};

#endif // SIZETORSTRING_HPP
