// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TupleRef.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/24 12:59:48 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/24 15:07:14 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FT_TUPLEREF_HPP
# define FT_TUPLEREF_HPP

# include <tuple>
# include <iostream> //debug

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

	TupleRef(Args &...args) : tup(args...) {
		std::cout << typeid(*this).name() << std::endl;
		std::cout << typeid(this->tup).name() << std::endl;
	}
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
