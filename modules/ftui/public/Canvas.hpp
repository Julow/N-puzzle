// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Canvas.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:16:40 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/23 09:44:40 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ACANVAS_HPP
# define ACANVAS_HPP

# include <stdint.h>

# include "ft/Color.hpp"
# include "ft/Rect.hpp"
# include "ft/Vec.hpp"
# include "ft/utils.hpp"

# include "ftui/ftlua_extend.hpp"
# include "ftui/libftui.hpp"

namespace ftui
{

/*
** Canvas
** -
** Draw
** -
** TODO: default font
** TODO: ACanvas
*/
class	Canvas
{
public:
	typedef uint32_t	font_t;

/*
** ========================================================================== **
** Canvas::Params
** -
** 						drawRect			drawText
** strokeColor			Border color		-
** fillColor			Fill color			Text color
** lineWidth			Border width		Font size
** font					-					Font
*/
	struct	Params
	{
	public:
		ft::Color::t		strokeColor;
		ft::Color::t		fillColor;
		float				lineWidth;
		font_t				font;
	};

/*
** ========================================================================== **
*/
	Canvas(ft::Color::t *bitmap, int width, int height);
	Canvas				&operator=(Canvas &&rhs);
	virtual ~Canvas(void);

	Canvas(Canvas const &src) = delete;
	Canvas				&operator=(Canvas const &rhs) = delete;

	operator ftlua::Converter<Canvas>()
		{
			return ftlua::Converter<Canvas>(
				*this, [](lua_State *l, Canvas &v)
				{
					return ftlua::pushLightKey(l, &v);
				});
		}


/*
** ========================================================================== **
** Clip
** -
** The clip rect is used to clip shapes being drawn
** Drawings outside the clip are not processed
** -
** Warning: clear() functions are not affected by the clip
*/
	/*
	** Get the clip
	*/
	ft::Rect<int>		getClip(void) const;

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
** ========================================================================== **
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
** ========================================================================== **
** Alpha
** -
** Extra alpha applied to each drawings
*/
	float				getAlpha(void) const;

	void				applyAlpha(float alpha);
	void				setAlpha(float alpha);

/*
** ========================================================================== **
** Scale
** -
** TODO: scale is not fully implemented
*/
	void				setScale(float scale);
	float				getScale(void) const;

/*
** ========================================================================== **
** Drawing
*/
	/*
	** Draw a rect
	*/
	void				drawRect(ft::Rect<float> const &rect, Params const &p);

	/*
	** Draw text
	** -
	** opt.fillColor is used as text color
	** opt.lineWidth is used as font size
	*/
	void				drawText(ft::Vec2<float> pos, std::string const &text,
							Params const &opt);

/*
** ========================================================================== **
** Font
*/
	/*
	** Load a font file and return a font handler
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
** ========================================================================== **
** Lua interactions
*/
	static void			pushTemplate(lua_State *l);
	static int			drawRectG(lua_State *l);
	static int			drawTextG(lua_State *l);
	static int			measureTextG(lua_State *l);
	static int			setFontG(lua_State *l);

	void				pushLua(lua_State *l);
	bool				isInLua(lua_State *l);

/*
** ========================================================================== **
** Bitmap
*/
	ft::Color::t const	*getBitmap(void) const;

	int					getBitmapWidth(void) const;
	int					getBitmapHeight(void) const;

	/*
	** Clear the whole canvas (or 'rect') with transparent (0x0) pixels
	*/
	void				clear(void);
	void				clear(ft::Rect<int> const &rect);

/*
** ========================================================================== **
** Changed rect
** -
** Sum of bounds of all drawings
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
