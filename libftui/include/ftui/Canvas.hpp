// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Canvas.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:16:40 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/09 18:01:16 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ACANVAS_HPP
# define ACANVAS_HPP

# include <stdint.h>

# include "ftui/libftui.hpp"
# include "ft/Color.hpp"
# include "ft/Rect.hpp"
# include "ft/Vec.hpp"

namespace ftui
{

/*
** Canvas
** -
** Draw
** -
** Warning: copy constructor and assignation does not delete/copy the bitmap
*/
class	Canvas
{
public:
	struct	Params
	{
	public:
		ft::Color::t	strokeColor;
		ft::Color::t	fillColor;
		int32_t			lineWidth;
		// float		borderRound;
	};

	Canvas(ft::Color::t *bitmap, int width, int height);
	Canvas(Canvas const &src);
	virtual ~Canvas(void);

	Canvas			&operator=(Canvas const &rhs);

/*
** Bitmap
*/
	ft::Color::t const	*getBitmap(void) const;

	int				getBitmapWidth(void) const;
	int				getBitmapHeight(void) const;

	inline void		putPixel(int x, int y, ft::Color::t color)
	{
		y = y * _width + x;
		if (ft::Color::a(color) < 255)
			_bitmap[y] = ft::Color::put(_bitmap[y], color);
		else
			_bitmap[y] = color;
	}

	inline void		putPixel(int x, int y, ft::Color::t color, int n)
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

	void			clear(void);
	void			clear(ft::Rect<int> const &rect);

/*
** Clip
** -
** The clip is used to change the size and origin of shape being drawn
** So rect filled with fillRect(0, 0, ...) are draw inside the clip
** The clip is usualy applied and restored by layouts
** Warning: clear(ft::Rect<int> const&) is not affected by the clip
*/
	ft::Rect<int> const	&getClip(void) const;

	int				getWidth(void) const;
	int				getHeight(void) const;

	void			applyClip(ft::Rect<int> const &rect);
	void			setClip(ft::Rect<int> const &rect);

	void			clearClip(void);

/*
** Alpha
*/
	float			getAlpha(void) const;

	void			applyAlpha(float alpha);
	void			setAlpha(float alpha);

/*
** Drawing
*/
	void			strokeRect(ft::Rect<int> const &rect, Params const &opt);
	void			fillRect(ft::Rect<int> const &rect, Params const &opt);

	// void		strokeLine(Vec2<int> a, Vec2<int> b, Params const &opt);
	// void		strokeText(Vec2<int> pos, std::string const &text, Params const &opt);

protected:

	ft::Color::t	*_bitmap;
	int				_width;
	int				_height;

	ft::Rect<int>	_clip;

	float			_alpha;

private:
	Canvas(void);
};

};

#endif
