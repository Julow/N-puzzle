// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GlCanvas.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/24 10:06:54 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/24 11:34:38 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GLCANVAS_HPP
# define GLCANVAS_HPP

# include "ftui/ACanvas.hpp"
# include "ft/Color.hpp"

namespace gl
{

class	GlCanvas : public ftui::ACanvas
{
public:
	GlCanvas(ft::Color::t *bitmap, int width, int height);
	virtual ~GlCanvas(void);

	virtual void		clear(void);
	virtual void		clear(ft::Rect<int> const &rect);

	ft::Color::t const	*getBitmap(void) const;
	void				setBitmap(ft::Color::t *bitmap);

protected:

	ft::Color::t		*_bitmap;

	virtual void		_strokeRect(ft::Rect<int> const &rect,
							ft::Color::t color, int lineWidth);
	virtual void		_fillRect(ft::Rect<int> const &rect,
							ft::Color::t color);
	virtual void		_putAlphaBitmap(ft::Vec2<int> pos,
							uint8_t const *bitmap, ft::Rect<int> const &rect,
							int pitch, ft::Color::t color);

	inline void			putPixel(int x, int y, ft::Color::t color)
	{
		y = y * _width + x;
		if (ft::Color::a(color) < 255)
			_bitmap[y] = ft::Color::put(_bitmap[y], color);
		else
			_bitmap[y] = color;
	}

	inline void			putPixel(int x, int y, ft::Color::t color, int n)
	{
		x += y * _width;
		n += x;
		if (ft::Color::a(color) < 255)
			while (x < n)
			{
				_bitmap[x] = ft::Color::put(_bitmap[x], color);
				x++;
			}
		else
			while (x < n)
				_bitmap[x++] = color;
	}

private:
	GlCanvas(void) = delete;
	GlCanvas(GlCanvas const &src) = delete;
	GlCanvas			&operator=(GlCanvas const &rhs) = delete;
};

};

#endif
