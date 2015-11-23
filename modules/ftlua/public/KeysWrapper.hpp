// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   KeysWrapper.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:23:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/23 09:55:00 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_KEYSWRAPPER_HPP
# define FTLUA_KEYSWRAPPER_HPP

# include <tuple>

# include "liblua/lua.hpp"

namespace ftlua
{

template<typename... ARGS>
struct KeysWrapper
{

	/* CONSTRUCTION ***************** */
	KeysWrapper(ARGS const &...args)	: tup{args...} { }
	KeysWrapper(KeysWrapper &&src)		: tup(src.tup) { }
	~KeysWrapper(void) { }

	KeysWrapper() = delete;
	KeysWrapper(KeysWrapper const &src) = delete;
	KeysWrapper				&operator=(KeysWrapper const &rhs) = delete;
	KeysWrapper				&operator=(KeysWrapper &&rhs) = delete;

	/* ATTRIBUTES ******************* */
	typedef std::tuple<ARGS const &...>		tuple_t;
	tuple_t const			tup;

	static_assert(sizeof...(ARGS) > 0, "This should hold at least one key");

};

template<typename... ARGS>
KeysWrapper<ARGS...>		make_keys(ARGS const& ...args)
{
	return KeysWrapper<ARGS...>(args...);
}

};

#endif /* *************************************************** KEYSWRAPPER_HPP */
