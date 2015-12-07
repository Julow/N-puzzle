// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TupleRef.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/24 12:59:48 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 15:36:22 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FT_TUPLEREF_HPP
# define FT_TUPLEREF_HPP

# include <tuple>
# include <typeinfo>

namespace ft // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


class ITupleRef
{
public:
	virtual ~ITupleRef() {}
};

template <class ...Args>
class TupleRef : public ITupleRef
{
public:

	std::tuple<Args &...>		tup;

	TupleRef(Args &...args) : tup(args...) {}
	TupleRef(TupleRef const &src) : tup(src.tup) {}
	~TupleRef() {}

	TupleRef					&operator=(TupleRef const &rhs)
		{
			this->tup = rhs.tup;
			return *this;
		}

};

template <class ...Args>
TupleRef<Args...>				make_tupleref(Args &...args)
{
	return TupleRef<Args...>(args...);
}

}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FT //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


#endif /* *************************************************** FT_TUPLEREF_HPP */
