// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   KeysWrapper.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:23:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/19 13:26:49 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_KEYSWRAPPER_HPP
# define FTLUA_KEYSWRAPPER_HPP

# include <tuple>

namespace ftlua
{

template<typename HEAD, typename... TAIL>
class KeysWrapper
{

	/* CONSTRUCTION ***************** */
public:
	KeysWrapper(HEAD const &h, TAIL const &...t) : _head(h), _tail{t...} { }
	~KeysWrapper(void) { }

	KeysWrapper() = delete;
	KeysWrapper(KeysWrapper const &src) = delete;
	KeysWrapper(KeysWrapper &&src) = delete;
	KeysWrapper				&operator=(KeysWrapper const &rhs) = delete;
	KeysWrapper				&operator=(KeysWrapper &&rhs) = delete;

	/* UNPACKING ******************** */
	HEAD const				&head(void) const
		{ return this->_head; }

	KeysWrapper<TAIL...>	tail(void) const
		{ return KeysWrapper<TAIL...>(this->_tail); }

	/* ATTRIBUTES ******************* */
private:
	HEAD const							&_head;
	std::tuple<TAIL const &...>	const	_tail;

};

};

#endif /* *************************************************** KEYSWRAPPER_HPP */
