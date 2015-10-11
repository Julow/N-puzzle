// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   math.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/11 11:32:38 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/11 11:32:56 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CONSTEXPRMATH_HPP
# define CONSTEXPRMATH_HPP

# include <type_traits>
# include <cmath>

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
constexpr T			factorial(T x)
{
	T	ret(x);

	while ((x -= static_cast<T>(1)) > static_cast<T>(0))
		ret *= x;
	return (ret);
}

template<typename T>
constexpr T			sqrt(T z)
{
	static_assert(std::is_floating_point<T>::value, "ftce::sqrt only takes floating points types");
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
	static_assert(std::is_floating_point<T>::value, "ftce::cos only takes floating points types");
	while (x > M_PI)
		x -= static_cast<T>(2. * M_PI);
	while (x < -M_PI)
		x += static_cast<T>(2. * M_PI);
	return (static_cast<T>(1)
		- (ftce::pow<T>(x, 2) / static_cast<T>(2))
		+ (ftce::pow<T>(x, 4) / static_cast<T>(24))
		- (ftce::pow<T>(x, 6) / static_cast<T>(720))
		+ (ftce::pow<T>(x, 8) / static_cast<T>(40320))	// MaxError: +0.0239781(-2.3978114%)
		- (ftce::pow<T>(x, 10) / static_cast<T>(3628800))	// MaxError: +0.0018293(-0.1829267%)
		+ (ftce::pow<T>(x, 12) / static_cast<T>(479001600))	// MaxError: +0.0001009(-0.0100911%)
		// - (ftce::pow(x, 14) / ftce::factorial(14))	// MaxError: +0.0070322(-0.7032156%)
		// + (ftce::pow(x, 16) / ftce::factorial(16))	// MaxError: +0.0378902(-3.7890196%)
		);
}

template<typename T>
constexpr T			sin(T x) // untested
{
	static_assert(std::is_floating_point<T>::value, "ftce::sin only takes floating points types");
	while (x > M_PI)
		x -= static_cast<T>(2. * M_PI);
	while (x < -M_PI)
		x += static_cast<T>(2. * M_PI);
	return (x
		- (ftce::pow<T>(x, 3) / static_cast<T>(6))
		+ (ftce::pow<T>(x, 5) / static_cast<T>(120))
		- (ftce::pow<T>(x, 7) / static_cast<T>(5040))
		+ (ftce::pow<T>(x, 9) / static_cast<T>(362880))
		- (ftce::pow<T>(x, 11) / static_cast<T>(39916800))
		+ (ftce::pow<T>(x, 13) / static_cast<T>(6227020800LL))
		);
}

template<typename T>
constexpr T			ceil(T x)
{
	const T		r = static_cast<T>(static_cast<int>(x));

	return ((r == x) ? r : (x > zeroi_t()) ? r + onei_t() : r); //A VERIFIER !!
}

template<typename T>
constexpr T			floor(T x)
{
	const T		r = static_cast<T>(static_cast<int>(x));

	return ((r == x) ? r : (x > zeroi_t()) ? r : r - onei_t()); //A VERIFIER !!
}

template<typename T>
constexpr int	round_toi(T x)
{
	static_assert(std::is_floating_point<T>::value
				  , "round_toi takes floating point types");
	if (x > static_cast<T>(zeroi_t()))
		return static_cast<int>(x + static_cast<T>(0.5f));
	return static_cast<int>(x - static_cast<T>(0.5f));
}

template<typename T>
constexpr T const	&max(T const &x, T const &y)
{
	if (x > y)
		return (x);
	return (y);
}

template<typename T>
constexpr T			fmod(T x, T y)
{
	while(x < static_cast<T>(0))
		x += y;
	while(x > y)
		x -= y;
	return (x);
}

};

#endif
