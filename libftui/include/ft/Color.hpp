// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Color.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/09 17:05:13 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/09 23:26:08 by juloo            ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef COLOR_HPP
# define COLOR_HPP

# include <stdint.h>
# include <iostream> // TODO remove
#include <iomanip> // TODO remove

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
	static t			put(t dst, t src)
	{
		uint32_t const	dst_a = a(dst);
		uint32_t const	src_a = a(src);
		uint32_t const	out_a = (src_a + (dst_a * (256 - src_a) / 256)) * 256;

		return ((out_a << 16)
		| (((256 - dst_a) * (dst_a * r(dst) + (src_a * r(src))) / out_a) << 16)
		| (((256 - dst_a) * (dst_a * g(dst) + (src_a * g(src))) / out_a) << 8)
		| (((256 - dst_a) * (dst_a * b(dst) + (src_a * b(src))) / out_a)));
	}

// 	static t			put(t dst, t src)
// 	{
// 		uint32_t const		dst_a = a(dst);
// 		uint32_t const		src_a = a(src);
// 		uint32_t const		out_a = src_a + (dst_a * (256 - src_a) / 256);

// 		return (
// 			(out_a << 24)
// | ((
// 	(((r(dst) * dst_a / 256) + (r(src) * src_a / 256)) * (256 - dst_a))
// 			/ out_a
// ) << 16)
// | ((
// 	(((g(dst) * dst_a / 256) + (g(src) * src_a / 256)) * (256 - dst_a))
// 			/ out_a
// ) << 8)
// | ((
// 	(((b(dst) * dst_a / 256) + (b(src) * src_a / 256)) * (256 - dst_a))
// 			/ out_a
// ))
// 		);
// 	}

	static void			print(std::ostream &o, t color) // TODO remove
	{
		o << "0x"
			<< std::setbase(16) << std::setw(2) << std::setfill('0') << (int)a(color)
			<< std::setbase(16) << std::setw(2) << std::setfill('0') << (int)r(color)
			<< std::setbase(16) << std::setw(2) << std::setfill('0') << (int)g(color)
			<< std::setbase(16) << std::setw(2) << std::setfill('0') << (int)b(color);
	}

	static void			debug(t color)
	{
		std::cout << "rgba: "
			<< (int)r(color) << ", "
			<< (int)g(color) << ", "
			<< (int)b(color) << ", "
			<< (int)a(color) << " ; put on 0xFFFFFFFF: ";
		Color::print(std::cout, put(0xFFFFFFFF, color)); std::cout << " ; put on 0x7FFFFFFF: ";
		Color::print(std::cout, put(0x7FFFFFFF, color)); std::cout << std::endl;
			// << (int)a(color) << " ; zero: ";
		// Color::print(std::cout, a(color, 0)); std::cout << ", ";
		// Color::print(std::cout, r(color, 0)); std::cout << ", ";
		// Color::print(std::cout, g(color, 0)); std::cout << ", ";
		// Color::print(std::cout, b(color, 0)); std::cout << " ; 1: ";
		// Color::print(std::cout, alpha(color, 1.f)); std::cout << " ; 0.5: ";
		// Color::print(std::cout, alpha(color, 0.5f)); std::cout << std::endl;
	}

protected:

private:
	Color(void);
	Color(Color const &src);
	Color			&operator=(Color const &rhs);
};

};

#endif
