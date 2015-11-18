
#include <type_traits>
#include <cstdint>
#include <iostream>
typedef void		lua_State;

namespace ftlua
{

// KEY
template<typename... ARGS>
class KeysWrapper
{
public:
	KeysWrapper(ARGS const &...args)
		: _tup{args...}
		{ }
	 ~KeysWrapper(void)
		{ }

private:
	typedef std::tuple<ARGS const &...>		tuple_t;
	tuple_t const		_tup;

// ftassert size > 0

};

template<typename... ARGS>
KeysWrapper<ARGS...>	make_key(ARGS const &...args)
{
	return KeysWrapper<ARGS...>{args...};
}

//PUSH
template<bool USELUAERR = false, class T>
void			push(lua_State *l, T const &)
{
	static_assert(!std::is_same<T, T>::value, "No");
	return ;
}

template<bool USELUAERR = false, class T = int>
void			push(lua_State *l, int const &i)
{
	std::cout << "push:" << i << '(' << USELUAERR << ')' << std::endl;

	return ;
}

template<bool USELUAERR = false
		 , typename... ARGS, class T = KeysWrapper<ARGS...> >
void			push(lua_State *l, KeysWrapper<ARGS...> const &wrap)
{
	std::cout << "salut" << std::endl;

	return ;
}

typedef std::nullptr_t	nil_t;
static nil_t			nil{};

};

int							main(void)
{
	void			*trux = (void*)0x42;
	lua_State		*l;

	ftlua::push(l, 42);
	ftlua::push<true>(l, 42);
	ftlua::push<false>(l, 42);
	// make_key(trux, "callbacks", 18);
	ftlua::push(l, ftlua::make_key(trux, "callbacks", 18));

	// push(nil);
	// make_asGKeys(42);
	// push(make_asGKeys(42));
	// push<true>(make_asGKeys(42));
	// push<false>(make_asGKeys(42));

	return (0);
}
