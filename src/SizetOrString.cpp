/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SizetOrString.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 07:10:34 by aistok            #+#    #+#             */
/*   Updated: 2026/02/16 16:14:37 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SizetOrString.hpp"

SizetOrString::SizetOrString(size_t value) : _type(SIZET), _st(value)
{
    /* done */
}

SizetOrString::SizetOrString(const std::string &value) : _type(STRING), _s(value)
{
    /* done */
}

SizetOrString::SizetOrString(const char *value) : _type(STRING), _s(value)
{
    /* done */
}

SizetOrString::Type SizetOrString::type() const
{
    return _type;
}

size_t SizetOrString::asSize_t() const
{
    return _st;
}

const std::string &SizetOrString::asString() const
{
    return _s;
}
