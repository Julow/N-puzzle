// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Array.tpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/01 15:59:31 by ngoguey           #+#    #+#             //
//   Updated: 2015/06/01 15:59:32 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

// * CONSTRUCTORS *********************************************************** //
template<typename T, size_t S>
constexpr Array<T, S>::Array() :
	_data(),
	_lastIndex(0)
{
	return ;
}

template<typename T, size_t S>
constexpr  Array<T, S>::Array(Array<T, S> const &src) :
	_data(),
	_lastIndex(src._lastIndex)
{
	for (size_t i = 0; i < S; i++)
		this->_data[i] = src._data[i];
	return ;
}

// * OPERATORS ************************************************************** //
template<typename T, size_t S>
constexpr Array<T, S>		&Array<T, S>::operator=(Array<T, S> const &rhs)
{
	this->_lastIndex = rhs._lastIndex;
	for (size_t i = 0; i < S; i++)
		this->_data[i] = rhs._data[i];
	return (*this);
}

template<typename T, size_t S>
constexpr T					&Array<T, S>::operator[](size_t s)
{
	//check overflow?
	if (s > this->_lastIndex)
		this->_lastIndex = s;
	return (this->_data[s]);
}

template<typename T, size_t S>
constexpr T const			&Array<T, S>::operator[](size_t s) const
{
	//check overflow?
	return (this->_data[s]);
}

// * MEMBER FUNCTIONS / METHODS ********************************************* //
template<typename T, size_t S>
typename Array<T, S>::iterator	Array<T, S>::begin(void) const
{
	typename Array<T, S>::iterator	it;

	it.setPtr(this->_data);
	// it.setPtr(&this->_data[0]);
	return (it);
}
template<typename T, size_t S>
typename Array<T, S>::iterator	Array<T, S>::end(void) const
{
	typename Array<T, S>::iterator	it;

	it.setPtr(this->_data + (this->_lastIndex + 1));
	// it.setPtr(&this->_data[this->_lastIndex + 1]);
	return (it);
}

template<typename T, size_t S>
constexpr size_t			Array<T, S>::getLastIndex(void) const
{
	return (this->_lastIndex);
}

template<typename T, size_t S>
constexpr size_t			Array<T, S>::size(void) const
{
	// return (this->_lastIndex);
	return (S);
}

// * NESTED_CLASSES ********************************************************* //

// * CTORS / DTORS ************** //
template<typename T, size_t S>
Array<T, S>::iterator::iterator()
{
	return ;
}
template<typename T, size_t S>
Array<T, S>::iterator::~iterator()
{
	return ;
}
template<typename T, size_t S>
Array<T, S>::iterator::iterator(
	typename Array<T, S>::iterator const &src)
{
	iterator::operator=(src);
	return ;
}
	// * OPERATORS ****************** //
template<typename T, size_t S>
typename Array<T, S>::iterator	&Array<T, S>::iterator::operator=(
	typename Array<T, S>::iterator const &rhs)
{
	_ptr = rhs._ptr;
	return (*this);
}
template<typename T, size_t S>
bool						Array<T, S>::iterator::operator!=(
	typename Array<T, S>::iterator const &rhs)
{
	return (_ptr != rhs._ptr);
}
template<typename T, size_t S>
typename Array<T, S>::iterator	&Array<T, S>::iterator::operator++(
	void)
{
	_ptr++;
	return (*this);
}

template<typename T, size_t S>
T const						&Array<T, S>::iterator::operator*(void) const
{
	return (*_ptr);
}
	// * MEMBER FUNCTIONS / METHODS * //
template<typename T, size_t S>
void						Array<T, S>::iterator::setPtr(T const *ptr)
{
	this->_ptr = ptr;
	return ;
}
