// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   types.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:12:33 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/02 17:43:56 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_TYPES_HPP
# define FTLUA_TYPES_HPP

# include <cstddef>

# include "ftlua/KeysWrapper.hpp"

namespace ftlua
{

typedef struct {}		nil_t;
static nil_t			nil{};

typedef struct {}		newtab_t;
static newtab_t			newtab;

typedef struct {int i;}	dup_t;
inline dup_t			dup(int i)
{ return dup_t{i}; }

};

#endif
