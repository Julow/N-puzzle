// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Canvas.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:16:40 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/08 11:21:06 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ACANVAS_HPP
# define ACANVAS_HPP

# include "ftui/libftui.hpp"
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
	typedef unsigned long int		color_t;

	struct	Params
	{
	public:
		color_t		strokeColor;
		color_t		fillColor;
		// float		strokeSize;
		// float		borderRound;
	};

	Canvas(color_t *bitmap, int width, int height);
	Canvas(Canvas const &src);
	virtual ~Canvas(void);

	Canvas			&operator=(Canvas const &rhs);

/*
** Bitmap
*/
	color_t const	*getBitmap(void) const;

	int				getWidth(void) const;
	int				getHeight(void) const;

	inline void		putPixel(int x, int y, color_t color)
	{
		_bitmap[y * _width + x] = color;
	}

	inline void		putPixel(int x, int y, color_t color, int n)
	{
		x += y * _width;
		n += x;
		while (x < n)
			_bitmap[x++] = color;
	}

	void			clear(ft::Rect<int> const &rect);

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

	color_t			*_bitmap;
	int				_width;
	int				_height;

	float			_alpha;

private:
	Canvas(void);
};

};

#endif
