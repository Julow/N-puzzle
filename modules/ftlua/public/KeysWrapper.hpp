// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   KeysWrapper.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:23:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 15:36:00 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_KEYSWRAPPER_HPP
# define FTLUA_KEYSWRAPPER_HPP

# include <tuple>

# include "liblua/lua.hpp"

namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template<int Relative = 0, typename... ARGS>
struct KeysWrapper
{
	static_assert(sizeof...(ARGS) > 0, "This should hold at least one key");

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

};

template<int Relative = 0, typename... ARGS>
KeysWrapper<Relative, ARGS...>		makeKeys(ARGS const& ...args)
{
	return KeysWrapper<Relative, ARGS...>(args...);
}


}; // ~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


#endif /* *************************************************** KEYSWRAPPER_HPP */
