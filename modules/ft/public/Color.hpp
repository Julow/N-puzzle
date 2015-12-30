// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Color.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/09 17:05:13 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/15 16:40:32 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef COLOR_HPP
# define COLOR_HPP

# include "ft/assert.hpp"

# include <stdint.h>
# include <algorithm>

namespace ft
{

/*
** Color::t represent a 32 bit color
**  with 4 channels (argb) of range 256 each (0-255)
** Color::t can safely be used as base type for color buffers
** (OpenGL handle it as GL_BGRA)
** -
** Can safely be writen in 0xFFFFFFFF (0xAARRGGBB) style
**  (2 digit per component)
** -
** TODO: handle gamma
*/
class	Color
{
public:
	virtual ~Color(void);

	typedef uint32_t	t;

	static inline t			make(uint32_t a, uint32_t r, uint32_t g, uint32_t b) // TODO: check, uint8 instead of uint38 ???
	{
		return ((a << 24) | (r << 16) | (g << 8) | (b << 0));
	}

	/*
	** Return the corresponding color component (r, g, b, a)
	*/
	static inline uint8_t	a(t color) { return ((uint8_t)(color >> 24)); }
	static inline uint8_t	r(t color) { return ((uint8_t)(color >> 16)); }
	static inline uint8_t	g(t color) { return ((uint8_t)(color >> 8)); }
	static inline uint8_t	b(t color) { return ((uint8_t)(color >> 0)); }

	/*
	** Return the corresponding color component (r, g, b, a)
	*/
	static inline t			a(t c, uint8_t a) { return ((c & 0x00FFFFFF) | (((t)a) << 24)); }
	static inline t			r(t c, uint8_t r) { return ((c & 0xFF00FFFF) | (((t)r) << 16)); }
	static inline t			g(t c, uint8_t g) { return ((c & 0xFFFF00FF) | (((t)g) << 8)); }
	static inline t			b(t c, uint8_t b) { return ((c & 0xFFFFFF00) | (((t)b) << 0)); }

	/*
	** Return 'color' after applying the alpha
	*/
	static inline t			alpha(t color, float alpha)
	{
		return (a(color, a(color) * alpha));
	}

	static inline t			alpha(t color, uint8_t alpha)
	{
		return (a(color, a(color) * alpha / 256));
	}

	/*
	** Return the result of putting 'src' over 'dst'
	** -
	** out_alpha = src_a + (dst_a * (256 - src_a) / 256)
	** out_rgb = ((dst_rgb * dst_a / 256) + (src_rgb * src_a / 256))
	** 					* (256 - dst_a) / out_alpha
	*/
	static inline t			put(t dst, t src)
	{
		uint32_t const	dst_a = a(dst);
		uint32_t const	src_a = a(src);
		uint32_t const	dst_fact = dst_a * (255 - src_a);
		uint32_t const	out_a = src_a + (dst_a * (255 - src_a) / 255);

		return make(
			out_a
			, std::min((r(src) * src_a + r(dst) * dst_fact / 255) / out_a, 255u)
			, std::min((g(src) * src_a + g(dst) * dst_fact / 255) / out_a, 255u)
			, std::min((b(src) * src_a + b(dst) * dst_fact / 255) / out_a, 255u)
			);

	}

protected:

private:
	Color(void);
	Color(Color const &src);
	Color			&operator=(Color const &rhs);
};

};

#endif
