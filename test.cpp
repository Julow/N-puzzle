
#include <type_traits>
#include <cstdint>
#include <iostream>

namespace ftlua
{

// KEY
template<typename... ARGS>
class KeyWrapper
{
public:
	KeyWrapper(ARGS const &...args)
		: _tup{args...}
		{ }
	 ~KeyWrapper(void)
		{ }

private:
	typedef std::tuple<ARGS const &...>		tuple_t;
	tuple_t const		_tup;

// ftassert size > 0

};

template<typename... ARGS>
KeyWrapper<ARGS...>	make_key(ARGS const &...args)
{
	return KeyWrapper<ARGS...>{args...};
}

//PUSH
template<bool USELUAERR = false, class T>
void			push(T const &)
{
	static_assert(!std::is_same<T, T>::value, "No");
	return ;
}

template<bool USELUAERR = false, class T = int>
void			push(int const &i)
{
	std::cout << "push:" << i << '(' << USELUAERR << ')' << std::endl;

	return ;
}

template<bool USELUAERR = false, typename... ARGS, class T = KeyWrapper<ARGS...> >
void			push(KeyWrapper<ARGS...> const &wrap)
{
	std::cout << "salut" << std::endl;

	return ;
}

typedef std::nullptr_t	nil_t;
static nil_t			nil{};

};
int							main(void)
{
	void	*trux = (void*)0x42;

	ftlua::push(42);
	ftlua::push<true>(42);
	ftlua::push<false>(42);
	// make_key(trux, "callbacks", 18);
	ftlua::push(ftlua::make_key(trux, "callbacks", 18));

	// push(nil);
	// make_asGKey(42);
	// push(make_asGKey(42));
	// push<true>(make_asGKey(42));
	// push<false>(make_asGKey(42));

	return (0);
}
