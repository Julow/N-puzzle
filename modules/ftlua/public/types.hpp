// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   types.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:12:33 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/19 12:23:19 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_TYPES_HPP
# define FTLUA_TYPES_HPP

# include <cstddef>

# include "ftlua/KeysWrapper.hpp"

namespace ftlua
{

typedef std::nullptr_t	nil_t;
static nil_t			nil{};

};

#endif