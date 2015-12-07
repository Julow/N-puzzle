// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Array.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/01 15:50:53 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 15:46:57 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ARRAY_CLASS_HPP
# define ARRAY_CLASS_HPP

namespace ftce //ft_ConstExpr
{
template<typename T, size_t S>
class Array
{
public:
	// * NESTED OBJECTS ************* //
	class iterator
	{
	public:
		iterator();
		iterator(iterator const &src);
		virtual ~iterator();
		
		iterator				&operator=(iterator const &rhs);
		bool					operator!=(iterator const &rhs);
		T const					&operator*(void) const;
		iterator				&operator++(void);
		
		void					setPtr(T const *ptr);
		
	private:
		T const					*_ptr;
	};
	
	// * CTORS / DTORS ************** //
	constexpr Array();
	constexpr Array(Array const &src);
	~Array() = default;
	
	// * OPERATORS ****************** //
	constexpr Array				&operator=(Array const &rhs);
	constexpr T					&operator[](size_t s);
	constexpr T const			&operator[](size_t s) const;
	
	// * MEMBER FUNCTIONS / METHODS * //
	constexpr size_t			getLastIndex(void) const;
	constexpr size_t			size(void) const;
	iterator					begin(void) const;
	iterator					end(void) const;
	
protected:
private:
	// * ATTRIBUTES ***************** //
	T							_data[S];
	size_t						_lastIndex;
};

#include "ftce/Array.tpp"
};

#endif // *************************************** ARRAY_CLASS_HPP //
