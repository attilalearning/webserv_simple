/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SizetOrString.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 07:10:34 by aistok            #+#    #+#             */
/*   Updated: 2026/02/16 16:11:35 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class SizetOrString
{
public:
	enum Type
	{
		SIZET,
		STRING
	};

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
