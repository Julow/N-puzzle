
#include <type_traits>
#include <cstdint>
#include <iostream>
typedef void		lua_State;
# include <tuple>

// ========================================================================== //
// CONVERTER ================================================================ //
# define DELPTR(T) typename std::remove_pointer<T>::type
# define DELCONST(T) typename std::remove_const<T>::type
# define ISCONV(A, B) std::is_convertible<A, B>::value
# define ISPTR(A) std::is_pointer<A>::value
# define ISCONST(A) std::is_const<A>::value
# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISSAME(A, B) std::is_same<A, B>::value

template<typename T
		 , OK_IF(!ISSAME(void, T))
		 >
struct Converter
{
	typedef int		(*push_t)(lua_State *l, T &);
	Converter(T &v, push_t p) : _v(v), _p(p) { }
	~Converter() {}

	int				callPush(lua_State *l)
		{
			std::cout << "Converter.callPush(l)" << std::endl;
			return this->_p(l, this->_v);
		}

private:
	T		&_v;
	push_t	_p;

};
// ========================================================================== //

template <bool USELUAERR>int push(lua_State *l, int &){std::cout << "int push" << std::endl; return 1;}
template <bool USELUAERR>int push(lua_State *l, void *&){ std::cout << "void* push" << std::endl; return 1;}
template <bool USELUAERR>int push(lua_State *l, bool &){ std::cout << "bool push" << std::endl; return 1;}

// Push (T to Converter<T>) || (const-T to Converter<const-T>)
template <bool USELUAERR, typename T
		  , OK_IF(ISCONV(T, Converter<T>)) >
int			push(lua_State *l, T &v)
{
	std::cout << "conv push" << std::endl;
	return Converter<T>{v}.callPush(l);
}

// Push (const-T to Converter<T>)
// Overload allowing const cast in User's cast-operator
template <bool USELUAERR, typename T
		  , OK_IF(ISCONST(T))
		  , typename NOCONST = DELCONST(T)
		  , OK_IF(ISCONV(T, Converter<NOCONST>)) >
int			push(lua_State *l, T &v)
{
	std::cout << "conv push" << std::endl;
	return Converter<NOCONST>{v}.callPush(l);
}

// Push (T* to push<T>) || (T-const * to push<T-const>)
template <bool USELUAERR, typename T
		  , OK_IF(ISPTR(T))
		  , typename NOPTR = DELPTR(T)
		  , typename NOPTRCONST = DELCONST(NOPTR)
		  , OK_IF(ISCONV(NOPTRCONST, Converter<NOPTRCONST>))
		  >
int			push(lua_State *l, T v)
{
	std::cout << "conv* push" << std::endl;
	return push<USELUAERR>(l, *v);
}



class AView
{
public:

	operator Converter<AView>()
		{ return Converter<AView>(*this, [](lua_State *, AView &){ return 12; }); }
	operator Converter<AView>() const
		{ return Converter<AView>(*const_cast<AView*>(this), [](lua_State *, AView &){ return 12; }); }
	// operator Converter<AView const>() const
	// 	{ return Converter<AView const>(*this, [](lua_State *, AView const &){ return 12; }); }

};
int							main(void)
{
	AView		v;
	AView const		vc{};
	void		*ptr;
	void const	*ptrc;
	lua_State *l = nullptr;

	push<false>(l, v);
	std::cout<<std::endl;

	push<false>(l, &v);
	std::cout<<std::endl;

	push<false>(l, vc);
	std::cout<<std::endl;

	push<false>(l, &vc);
	std::cout<<std::endl;

	push<false>(l, ptr);
	std::cout<<std::endl;

	// push<false>(l, ptrc);

}
