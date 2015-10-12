// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   math.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/11 11:32:38 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/11 17:53:46 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTCE_MATH_HPP
# define FTCE_MATH_HPP

# include <type_traits>
# include <cmath>
# include <cstdint>

/*
** WORK IN PROGRESS
*/

namespace ftce //ft_ConstExpr
{

typedef std::integral_constant<int, -1>		monei_t;
typedef std::integral_constant<int, 0>		zeroi_t;
typedef std::integral_constant<int, 1>		onei_t;
typedef std::integral_constant<int, 2>		twoi_t;

template<typename T>
constexpr T			factorial(T x)
{
	T	ret(x);

	while ((x -= static_cast<T>(1)) > static_cast<T>(0))
		ret *= x;
	return (ret);
}

typedef std::integral_constant<int, factorial(1)>					fact1_t;
typedef std::integral_constant<int, factorial(2)>					fact2_t;
typedef std::integral_constant<int, factorial(3)>					fact3_t;
typedef std::integral_constant<int, factorial(4)>					fact4_t;
typedef std::integral_constant<int, factorial(5)>					fact5_t;
typedef std::integral_constant<int, factorial(6)>					fact6_t;
typedef std::integral_constant<int, factorial(7)>					fact7_t;
typedef std::integral_constant<int, factorial(8)>					fact8_t;
typedef std::integral_constant<int, factorial(9)>					fact9_t;
typedef std::integral_constant<int, factorial(10)>					fact10_t;
typedef std::integral_constant<int, factorial(11)>					fact11_t;
typedef std::integral_constant<int, factorial(12)>					fact12_t;
typedef std::integral_constant<uint64_t, factorial<uint64_t>(13)>	fact13_t;
typedef std::integral_constant<uint64_t, factorial<uint64_t>(14)>	fact14_t;
typedef std::integral_constant<uint64_t, factorial<uint64_t>(15)>	fact15_t;
typedef std::integral_constant<uint64_t, factorial<uint64_t>(16)>	fact16_t;
typedef std::integral_constant<uint64_t, factorial<uint64_t>(17)>	fact17_t;
typedef std::integral_constant<uint64_t, factorial<uint64_t>(18)>	fact18_t;
typedef std::integral_constant<uint64_t, factorial<uint64_t>(19)>	fact19_t;
typedef std::integral_constant<uint64_t, factorial<uint64_t>(20)>	fact20_t;

template<typename T>
constexpr T			pow(T x, int p)
{
	T	ret(static_cast<T>(1));

	if (p > 0)
		for (int i = 0; i < p; i++)
			ret *= x;
	else if (p < 0)
		for (int i = 0; i < -p; i++)
			ret /= x;
	return (ret);
}

template<typename T>
constexpr T			sqrt(T z)// TO-DO improve
{
	static_assert(std::is_floating_point<T>::value
		, "ftce::sqrt only takes floating points types");
	T const		pow10[] = {1, 10, 100, 1000, 10000,
						   100000, 1000000, 10000000};
	T const		powm10[] = {1, 0.1L, 0.01L, 0.001L, 0.0001L,
							0.00001L, 0.000001L, 0.0000001L};
	T			ret = static_cast<T>(0);
	T			j = static_cast<T>(1);

	for(int i = 4 ; i > 0 ; i--)
	{
		T const		ip10 = pow10[i];
		T const		ip10square = ip10 * ip10;
		T const		ret2 = static_cast<T>(2.f) * ret;
		T const		ip10ret2 = ip10 * ret2;

		if (z - j * j * ip10square - j * ip10ret2 >= 0)
		{
			while(z - j * j * ip10square - j * ip10ret2 >= 0 && j < 10)
			{
				j++;
				if (j >= 10)
					break;
			}
			j--;
			z -= j * j * ip10square + j * ip10ret2;
			ret += j * ip10;
			j = static_cast<T>(1);
		}
	}
	for(int i = 0 ; i >= -4 ; i--)
	{
		T const		ip10 =  powm10[-i];
		T const		ret2 = static_cast<T>(2.f) * ret;
		T const		ip10square = ip10 * ip10;
		T const		ip10ret2 = ip10 * ret2;

		if (z - j * j * ip10square - j * ip10ret2 >= static_cast<T>(0))
		{
			while(z - j * j * ip10square - j * ip10ret2 >= static_cast<T>(0))
				j++;
			j--;
			z -= j * j * ip10square + j * ip10ret2;
			ret += j * ip10;
			j = static_cast<T>(1);
		}
	}
	return (ret);
}

template<typename T>
constexpr T			cos(T x)
{
	static_assert(std::is_floating_point<T>::value
		, "ftce::cos only takes floating points types");
	while (x > M_PI)// TO-DO improve
		x -= static_cast<T>(2. * M_PI);
	while (x < -M_PI)// TO-DO improve
		x += static_cast<T>(2. * M_PI);
	return (static_cast<T>(1)
		- ftce::pow<T>(x, 2) / static_cast<T>(fact2_t())
		+ ftce::pow<T>(x, 4) / static_cast<T>(fact4_t())
		- ftce::pow<T>(x, 6) / static_cast<T>(fact6_t())
		+ ftce::pow<T>(x, 8) / static_cast<T>(fact8_t())	// MaxError: +0.0239781(-2.3978114%)
		- ftce::pow<T>(x, 10) / static_cast<T>(fact10_t())	// MaxError: +0.0018293(-0.1829267%)
		+ ftce::pow<T>(x, 12) / static_cast<T>(fact12_t())	// MaxError: +0.0001009(-0.0100911%)
		// - (ftce::pow(x, 14) / ftce::factorial(14))	// MaxError: +0.0070322(-0.7032156%)
		// + (ftce::pow(x, 16) / ftce::factorial(16))	// MaxError: +0.0378902(-3.7890196%)
		);
}

template<typename T>
constexpr T			sin(T x) // untested
{
	static_assert(std::is_floating_point<T>::value
		, "ftce::sin only takes floating points types");
	while (x > M_PI)// TO-DO improve
		x -= static_cast<T>(2. * M_PI);
	while (x < -M_PI)// TO-DO improve
		x += static_cast<T>(2. * M_PI);
	return (x
		- ftce::pow<T>(x, 3) / static_cast<T>(fact3_t())
		+ ftce::pow<T>(x, 5) / static_cast<T>(fact5_t())
		- ftce::pow<T>(x, 7) / static_cast<T>(fact7_t())
		+ ftce::pow<T>(x, 9) / static_cast<T>(fact9_t())
		- ftce::pow<T>(x, 11) / static_cast<T>(fact11_t())
		+ ftce::pow<T>(x, 13) / static_cast<T>(fact13_t())
		);
}
// TO-DO Tan, Atan, PI-typed

template<typename T>
constexpr T			ceil(T x)
{
	static_assert(std::is_floating_point<T>::value
		, "ftce::ceil only takes floating points types");
	const T		r = static_cast<T>(static_cast<int64_t>(x));

	return (r == x) ? r : (x > zeroi_t()) ? r + onei_t() : r;// TO-DO improve
}

template<typename T>
constexpr T			floor(T x)
{
	static_assert(std::is_floating_point<T>::value
		, "ftce::floor only takes floating points types");
	const T		r = static_cast<T>(static_cast<int64_t>(x));

	return (r == x) ? r : (x > zeroi_t()) ? r : r - onei_t();// TO-DO improve
}

template<typename Ret = int, typename T>
constexpr Ret	round_toi(T x)
{
	static_assert(std::is_floating_point<T>::value
		, "ftce::round_toi only takes floating points types");
	if (x > static_cast<T>(zeroi_t()))
		return static_cast<Ret>(x + static_cast<T>(0.5f));
	return static_cast<Ret>(x - static_cast<T>(0.5f));
}

template<typename T>
constexpr T const	&max(T const &x, T const &y)
{
	return x > y ? x : y;
}


template<typename T>
constexpr T const	&min(T const &x, T const &y)
{
	return x < y ? x : y;
}

template<typename T>
constexpr T			mod_pos(T x, T y)
{
	while(x < static_cast<T>(0))// TO-DO improve
		x += y;
	while(x > y)// TO-DO improve
		x -= y;
	return x;
}

};

#endif
