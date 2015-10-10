// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Color.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/09 17:05:13 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/10 15:29:01 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef COLOR_HPP
# define COLOR_HPP

# include <stdint.h>

namespace ft
{

/*
** Color::t represent a 32 bit color
**  with 4 channels (argb) of range 256 each (0-255)
** Color::t can safely be used as base type for color buffers
** (OpenGL handle it as GL_BGRA)
** -
** Can be safely writen as 0xFFFFFFFF (0xAARRGGBB) style
**  (2 digit per component)
** -
** TODO: handle gamma
*/
class	Color
{
public:
	virtual ~Color(void);

	typedef uint32_t	t;

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

	/*
	** Return the result of putting 'src' in front of 'dst'
	** -
	** out_alpha = src_a + (dst_a * (256 - src_a) / 256)
	** out_rgb = ((dst_rgb * dst_a / 256) + (src_rgb * src_a / 256))
	**                 * (256 - dst_a) / out_alpha
	*/

	static inline t			put(t dst, t src)
	{
		uint32_t const	dst_a = a(dst);
		uint32_t const	src_a = a(src);
		uint32_t const	out_a = src_a + (dst_a * (256 - src_a) / 256);
		uint32_t const	tmp = out_a * 256 / (256 - std::min(dst_a, src_a));

		return ((out_a << 24)
			| (((dst_a * r(dst) + (src_a * r(src))) / tmp) << 16)
			| (((dst_a * g(dst) + (src_a * g(src))) / tmp) << 8)
			| (((dst_a * b(dst) + (src_a * b(src))) / tmp)));
	}

protected:

private:
	Color(void);
	Color(Color const &src);
	Color			&operator=(Color const &rhs);
};

};

#endif
