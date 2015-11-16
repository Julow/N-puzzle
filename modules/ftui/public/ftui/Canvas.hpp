// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Canvas.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:16:40 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/16 15:43:34 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ACANVAS_HPP
# define ACANVAS_HPP

# include <stdint.h>

# include "ftui/libftui.hpp"
# include "ft/Color.hpp"
# include "ft/Rect.hpp"
# include "ft/Vec.hpp"
# include "ftlua/ftlua.hpp"

# include "ft/utils.hpp"

namespace ftui
{

/*
** Canvas
** -
** Draw
** -
** TODO: default font
** TODO: draw offset (replace clip) ??
** TODO: ACanvas
*/
class	Canvas
{
public:
	typedef uint32_t	font_t;

	struct	Params
	{
	public:
		ft::Color::t		strokeColor;
		ft::Color::t		fillColor;
		float				lineWidth;
		font_t				font;
		// float			borderRound;
	};

	Canvas(ft::Color::t *bitmap, int width, int height);
	Canvas				&operator=(Canvas &&rhs);
	virtual ~Canvas(void);

	Canvas(Canvas const &src) = delete;
	Canvas				&operator=(Canvas const &rhs) = delete;

/*
** Lua interactions
*/
	static void				pushTemplate(lua_State *l);
	static int				drawRectG(lua_State *l);
	static int				drawTextG(lua_State *l);
	static int				measureTextG(lua_State *l);
	static int				setFontG(lua_State *l);

	void					pushLua(lua_State *l);
	bool					isInLua(lua_State *l);

/*
** Bitmap
*/
	ft::Color::t const	*getBitmap(void) const;

	int					getBitmapWidth(void) const;
	int					getBitmapHeight(void) const;

	void				clear(void);
	void				clear(ft::Rect<int> const &rect);

/*
** Clip
** -
** The clip rect is used to clip shapes being drawn
** Drawings outside the clip are not processed
** -
** Warning: clear() functions are not affected by the clip
*/
	/*
	** Get the clip size
	*/
	int					getWidth(void) const;
	int					getHeight(void) const;
	ft::Vec2<int>		getSize(void) const;

	/*
	** Set the clip (both relative to the origin)
	*/
	void				setClip(ft::Rect<int> const &rect);
	void				setClip(ft::Vec2<int> size);

	/*
	** Clear the content of the clip
	*/
	void				clearClip(void);

/*
** Origin
** -
** The origin vec is used to offset shapes being drawn
** Generally used by layouts
*/
	/*
	** Set origin (relative)
	*/
	void				applyOrigin(ft::Vec2<int> apply);

	/*
	** Absolute origin
	*/
	ft::Vec2<int>		getOrigin(void) const;
	void				setOrigin(ft::Vec2<int> origin);

/*
** Alpha
*/
	float				getAlpha(void) const;

	void				applyAlpha(float alpha);
	void				setAlpha(float alpha);

/*
** Scale
*/
	void				setScale(float scale);
	float				getScale(void) const;

/*
** Drawing
*/
	/*
	** Draw a rect
	*/
	void				drawRect(ft::Rect<float> const &rect, Params const &opt);

	/*
	** Draw text
	** -
	** opt.fillColor is used as text color
	** opt.lineWidth is used as font size
	*/
	void				drawText(ft::Vec2<float> pos, std::string const &text,
							Params const &opt);

/*
** Font
*/
	/*
	** Return a font handler
	*/
	static font_t		getFont(std::string const &file);

	/*
	** Return the size of the text
	** -
	** opt.lineWidth is used as font size
	*/
	static ft::Vec2<int>	measureText(std::string const &text,
								Params const &opt);

/*
** Changed rect
*/
	ft::Rect<int> const	&getChangedRect(void) const;
	void				resetChangedRect(void);

protected:

	ft::Color::t		*_bitmap;
	int					_width;
	int					_height;

	ft::Rect<int>		_clip;

	ft::Vec2<int>		_origin;
	float				_alpha;
	float				_scale;

	ft::Rect<int>		_changedRect;

	font_t				_luaFont;

	void				_strokeRect(ft::Rect<int> const &rect, ft::Color::t color,
							int lineWidth);
	void				_fillRect(ft::Rect<int> const &rect, ft::Color::t color);

/*
** Bitmap
*/
	inline void			putPixel(int x, int y, ft::Color::t color)
	{
		y = y * _width + x;
		if (ft::Color::a(color) < 255)
		{
			_bitmap[y] = ft::Color::put(_bitmap[y], color);
		}
		else
		{
			_bitmap[y] = color;
		}
	}

	inline void			putPixel(int x, int y, ft::Color::t color, int n)
	{
/*		if (y == 100)
		{
			auto res = ft::Color::put(_bitmap[x + y * _width], color);
			ft::f(std::cout, "xy(%/%) n(%) putting(argb %/%/%/%)a(%f) on(argb %/%/%/%) ->(%/%/%/%)\n"
				  , x, y, n
				  , (int)ft::Color::a(color)
				  , (int)ft::Color::r(color)
				  , (int)ft::Color::g(color)
				  , (int)ft::Color::b(color)

				  , _alpha

				  , (int)ft::Color::a(_bitmap[x + y * _width])
				  , (int)ft::Color::r(_bitmap[x + y * _width])
				  , (int)ft::Color::g(_bitmap[x + y * _width])
				  , (int)ft::Color::b(_bitmap[x + y * _width])

				  , (int)ft::Color::a(res)
				  , (int)ft::Color::r(res)
				  , (int)ft::Color::g(res)
				  , (int)ft::Color::b(res)


				);
				}*/
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

	/*
	** Put 'color' applying alpha in 'bitmap'
	** 'pos'	Where to put
	** 'bitmap'	Alpha bitmap (1 byte per px)
	** 'rect'	The rect in 'bitmap' to put
	** 'pitch'	Size of a row (in bitmap)
	** 'color'	The color to put after applying alpha
	*/
	void				putAlphaBitmap(ft::Vec2<int> pos, uint8_t const *bitmap,
							ft::Rect<int> const &rect, int pitch,
							ft::Color::t color);

/*
** Changed Rect
*/
	void				applyChangedRect(ft::Vec2<int> vec);
	void				applyChangedRect(ft::Rect<int> const &rect);

/*
** Font
*/
	static font_t		loadFont(std::string const &file);

private:
	Canvas(void);
};

};

#endif
