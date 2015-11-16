// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Canvas.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:22 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/16 13:49:53 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/Canvas.hpp"
#include "ftlua/ftlua.hpp"
#include "ft/utils.hpp"

extern "C"
{

#include <ft2build.h>
#include FT_FREETYPE_H

}

#include <iostream> //d
#include <vector>
#include <unordered_map>
#include <algorithm>

#include <cmath>
#include <cfenv>

namespace ftui
{

/*
** Globals used to manage fonts
*/
static FT_Library			g_freetype;
static bool					g_freetype_init = false;
static std::unordered_map<std::string, Canvas::font_t> g_faces_cache;
static std::vector<FT_Face>	g_faces;

/*
** Construction
*/

Canvas::Canvas(ft::Color::t *bitmap, int width, int height) :
	_bitmap(bitmap),
	_width(width),
	_height(height),
	_clip(0, 0, width, height),
	_alpha(1.f),
	_scale(1.f),
	_luaFont(0)
{
	resetChangedRect();
	return ;
}

// Canvas::Canvas(Canvas const &src) :
// 	_bitmap(src._bitmap),
// 	_width(src._width),
// 	_height(src._height),
// 	_alpha(src._alpha)
// {
// }

Canvas::~Canvas(void)
{
	// not removed from any lua
	return ;
}

Canvas			&Canvas::operator=(Canvas &&rhs)
{
	_bitmap = rhs._bitmap;
	_width = rhs._width;
	_height = rhs._height;
	_alpha = rhs._alpha;
	rhs._bitmap = nullptr;
	return (*this);
}

/*
** ========================================================================== **
** LUA Interations
*/

int				Canvas::drawRectG(lua_State *l)
{
	Canvas *const		self = ftlua::retrieveSelf<Canvas>(l, 1);
	Canvas::Params		p;
	ft::Rect<float>		r;
	int const			top = lua_gettop(l);

	r.left = luaL_checknumber(l, 1);
	r.top = luaL_checknumber(l, 2);
	r.right = luaL_checknumber(l, 3);
	r.bottom = luaL_checknumber(l, 4);
	p.fillColor = luaL_checkinteger(l, 5);
	if (top >= 6)
		p.strokeColor = luaL_checkinteger(l, 6);
	else
		p.strokeColor = 0x0;
	if (top >= 7)
		p.lineWidth = luaL_checkinteger(l, 7);
	else
		p.lineWidth = 0x0;
	if (top > 7)
		luaL_error(l, "Too many parameters to drawRect");
	self->drawRect(r, p);
	// ftlua::stackdump(l);
	return (0);
}

int				Canvas::drawTextG(lua_State *l)
{
	Canvas *const		self = ftlua::retrieveSelf<Canvas>(l, 1);
	Canvas::Params		params;
	ft::Vec2<float>		pos;
	std::string			text;
	int const			top = lua_gettop(l);

	text = luaL_checkstring(l, 1);
	pos.x = luaL_checknumber(l, 2);
	pos.y = luaL_checknumber(l, 3);
	params.fillColor = luaL_checkinteger(l, 4);
	params.lineWidth = luaL_checkinteger(l, 5);
	params.font = self->_luaFont;
	if (top > 5)
		luaL_error(l, "Too many parameters to drawRect");
	self->drawText(pos, text, params);
	return (0);
}

int				Canvas::setFontG(lua_State *l)
{
	Canvas *const		self = ftlua::retrieveSelf<Canvas>(l, 1);

	self->_luaFont = Canvas::getFont(luaL_checkstring(l, 1));
	return (0);
}

int				Canvas::measureTextG(lua_State *l)
{
	Canvas *const		self = ftlua::retrieveSelf<Canvas>(l, 1);
	ft::Vec2<int>		measure;
	std::string			text;
	Canvas::Params		params;

	text = luaL_checkstring(l, 1);
	params.lineWidth = luaL_checkinteger(l, 2);
	params.font = self->_luaFont;
	measure = self->measureText(text, params);
	lua_pop(l, lua_gettop(l));
	lua_pushinteger(l, measure.x);
	lua_pushinteger(l, measure.y);
	return (2);
}

void			Canvas::pushTemplate(lua_State *l)
{
	luaL_dostring(l, "Canvas = {}; Canvas.__index = Canvas;");
	ftlua::registerLuaCFunTable(l, "Canvas", "drawRect", &Canvas::drawRectG);
	ftlua::registerLuaCFunTable(l, "Canvas", "drawText", &Canvas::drawTextG);
	ftlua::registerLuaCFunTable(l, "Canvas", "measureText", &Canvas::measureTextG);
	ftlua::registerLuaCFunTable(l, "Canvas", "setFont", &Canvas::setFontG);
	return ;
}

void			Canvas::pushLua(lua_State *l)
{
	lua_pushglobaltable(l);				// _G
	lua_newtable(l);					// [], _G

	lua_pushlightuserdata(l, this);		// this, [], _G
	lua_pushvalue(l, -2);				// [], this, [], _G
	lua_settable(l, -4);				// [], _G

	if (lua_getglobal(l, "Canvas") != LUA_TTABLE)	// template, [], _G
		throw std::runtime_error("Canvas template should be present in _G");
	lua_setmetatable(l, -2);			// [], _G

	lua_pushinteger(l, 0);				// 0, [], _G
	lua_pushlightuserdata(l, this);		// this, 0, [], _G
	lua_settable(l, -3);				// [], _G

	lua_pop(l, 2);						// empty
	return ;
}

bool			Canvas::isInLua(lua_State *l)
{
	lua_pushglobaltable(l);
	lua_pushlightuserdata(l, this);
	if (lua_gettable(l, -2) != LUA_TTABLE)
	{
		lua_pop(l, 2);
		return false;
	}
	lua_pop(l, 2);
	return true;
}

/*
** ========================================================================== **
** Bitmap
*/
ft::Color::t const	*Canvas::getBitmap(void) const
{
	return (_bitmap);
}

int				Canvas::getBitmapWidth(void) const
{
	return (_width);
}

int				Canvas::getBitmapHeight(void) const
{
	return (_height);
}

void			Canvas::putAlphaBitmap(ft::Vec2<int> pos, uint8_t const *bitmap,
					ft::Rect<int> const &rect, int pitch, ft::Color::t color)
{
	int				x;
	int				y;
	ft::Color::t	col;

	ft::f(std::cout, "putAlphaBitmap at (%)\n ", pos);
	y = rect.top;
	while (y < rect.bottom)
	{
		x = rect.left;
		while (x < rect.right)
		{
			col = ft::Color::alpha(color, bitmap[x]);
			if (ft::Color::a(col) > 0)
				putPixel(x + pos.x, y + pos.y, ft::Color::alpha(color, bitmap[x]));
			// else
				// FTASSERT(false); //TODO: avoid reaching here
			x++;
		}
		y++;
		bitmap += pitch;
	}
}

void			Canvas::clear(void)
{
	memset(_bitmap, 0, _width * _height * sizeof(ft::Color::t));
}

void			Canvas::clear(ft::Rect<int> const &rect)
{
	int const	width = rect.getWidth() * sizeof(ft::Color::t);
	int			end;
	int			offset;

	offset = rect.top * _width + rect.left;
	end = rect.getHeight() * _width + offset;
	while (offset < end)
	{
		memset(_bitmap + offset, 0, width);
		offset += _width;
	}
}

/*
** ========================================================================== **
** Origin
*/
void			Canvas::setOrigin(ft::Vec2<int> origin)
{
	_origin = origin;
}

void			Canvas::applyOrigin(ft::Vec2<int> apply)
{
	_origin += apply;
}

ft::Vec2<int>	Canvas::getOrigin(void) const
{
	return (_origin);
}

/*
** ========================================================================== **
** Scale
*/
void			Canvas::setScale(float scale)
{
	_scale = scale;
}

float			Canvas::getScale(void) const
{
	return (_scale);
}

/*
** ========================================================================== **
** Clip
*/
ft::Rect<int> const	&Canvas::getClip(void) const
{
	return (_clip);
}

int				Canvas::getWidth(void) const
{
	return (_clip.getWidth());
}

int				Canvas::getHeight(void) const
{
	return (_clip.getHeight());
}

// void			Canvas::applyClip(ft::Rect<int> const &rect)
// {
// 	_clip.top += rect.top;
// 	_clip.left += rect.left;
// 	_clip.setSize(ft::make_vec(rect.getWidth(), rect.getHeight()));
// }

void			Canvas::setClip(ft::Rect<int> const &rect)
{
	_clip = rect;
}

void			Canvas::clearClip(void)
{
	clear(getClip());
}

/*
** ========================================================================== **
** Alpha
*/
float			Canvas::getAlpha(void) const
{
	return (_alpha);
}

void			Canvas::applyAlpha(float alpha)
{
	_alpha *= alpha;
}

void			Canvas::setAlpha(float alpha)
{
	_alpha = alpha;
}

/*
** ========================================================================== **
** Render rect
*/
void			Canvas::drawRect(ft::Rect<float> const &rect, Params const &opt)
{
	ft::Rect<int>	int_rect = static_cast<ft::Rect<int>>(rect * _scale);

	int_rect += _origin;
	// if (int_rect.right > _clip.right)
	// 	int_rect.right = _clip.right;
	// if (int_rect.bottom > _clip.bottom)
	// 	int_rect.bottom = _clip.bottom;
	if (ft::Color::a(opt.strokeColor) != 0)
	{
		_strokeRect(int_rect, ft::Color::alpha(opt.strokeColor, _alpha),
			opt.lineWidth);
		applyChangedRect(int_rect);
		if (ft::Color::a(opt.fillColor) != 0)
		{
			int_rect.expand(-opt.lineWidth * _scale);
			_fillRect(int_rect, ft::Color::alpha(opt.fillColor, _alpha));
		}
	}
	else if (ft::Color::a(opt.fillColor) != 0)
	{
		_fillRect(int_rect, ft::Color::alpha(opt.fillColor, _alpha));
		applyChangedRect(int_rect);
	}
}

void			Canvas::_strokeRect(ft::Rect<int> const &rect,
					ft::Color::t color, int lineWidth)
{
	int const		left = rect.left;
	int const		right = rect.right;
	int				top;
	int				y;

	if (rect.getWidth() == 0 || rect.getHeight() == 0)
		return ;
	y = rect.bottom - 1;
	top = std::max(rect.bottom - lineWidth, rect.top);
	while (y >= top)
		putPixel(left, y--, color, rect.getWidth());
	top = rect.top + lineWidth;
	while (y >= top)
	{
		putPixel(left, y, color, lineWidth);
		putPixel(right - lineWidth, y, color, lineWidth);
		y--;
	}
	top -= lineWidth;
	while (y >= top)
		putPixel(left, y--, color, rect.getWidth());
}

void			Canvas::_fillRect(ft::Rect<int> const &rect, ft::Color::t color)
{
	int const	left = rect.left;
	int const	top = rect.top;
	int const	width = rect.getWidth();
	int			y;

	y = rect.bottom;
	while (--y >= top)
		putPixel(left, y, color, width);
}

/*
** ========================================================================== **
** Render text
*/
void			Canvas::drawText(ft::Vec2<float> pos, std::string const &text,
					Params const &opt)
{
	ft::Vec2<int>	int_vec;
	FT_Face			face;
	FT_UInt			glyph_index;
	ft::Rect<int>	glyph_rect;

	int_vec = ft::make_vec(static_cast<int>(pos.x * _scale),
		static_cast<int>(pos.y * _scale));
	FTASSERT(ft::Color::a(opt.fillColor) != 0);
	FTASSERT(opt.lineWidth > 0);
	FTASSERT(opt.font < g_faces.size());
	if (ft::Color::a(opt.fillColor) == 0 || opt.lineWidth <= 0
		|| opt.font >= g_faces.size())
		return ;
	int_vec += _origin;
	ft::f(std::cout, "Drawing at '%' (%)  int_vec1(%)\n", text,  pos, int_vec);
	applyChangedRect(int_vec);
	face = g_faces[opt.font];
	if (FT_Set_Pixel_Sizes(face, 0, opt.lineWidth))
		throw std::runtime_error("Cannot resize font (drawText)");
	int_vec.y += opt.lineWidth;
	// int_vec.y += (face->descender * 2 + face->height + face->ascender) >> 6;
	// TODO: Fix les font height please
	for (uint32_t i = 0; i < text.size(); i++)
	{
		glyph_index = FT_Get_Char_Index(face, text[i]);
		if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
			continue ;
		if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
			continue ;
		glyph_rect.right = face->glyph->bitmap.width;
		glyph_rect.bottom = face->glyph->bitmap.rows;
		putAlphaBitmap(
			int_vec
			+ ft::make_vec(face->glyph->bitmap_left, -face->glyph->bitmap_top)
			,
			face->glyph->bitmap.buffer, glyph_rect, face->glyph->bitmap.pitch,
					   opt.fillColor);
		int_vec.x += face->glyph->advance.x >> 6;
	}
	applyChangedRect(int_vec);
	return ;
}

ft::Vec2<int>	Canvas::measureText(std::string const &text, Params const &opt)
{
	ft::Vec2<FT_Fixed>	size(0, 0);
	FT_Face				face;
	FT_UInt				glyph_index;

	FTASSERT(opt.lineWidth > 0);
	FTASSERT(opt.font < g_faces.size());
	if (opt.lineWidth <= 0 || opt.font >= g_faces.size())
		return (size);
	face = g_faces[opt.font];
	if (FT_Set_Pixel_Sizes(face, 0, opt.lineWidth))
		throw std::runtime_error("Cannot resize font (measureText)");
	for (uint32_t i = 0; i < text.size(); i++)
	{
		glyph_index = FT_Get_Char_Index(face, text[i]);
		if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
			continue ;
		size.x += face->glyph->advance.x;
		// size.y = std::max(size.y, face->glyph->advance.y);
	}
	// ft::f(std::cout, "texy % % %\n", face->height >> 6
		  // , face->ascender >> 6, face->descender >> 6);
	size.x >>= 6;
	// size.y >>= 6;
	// size.y = face->bbox.yMax;
	// size.y = 12;
	// size.y = face->size;
	// ft::f(std::cout, "asc%  desc%  em%\n"
	// 	  , face->ascender / 64
	// 	  , face->descender / 64
	// 	  , face->units_per_EM / 64
	// 	);
	// TODO: Fix les font height please
	size.y = opt.lineWidth;
	// size.y = (face->ascender - face->descender) >> 6;
	// size.y = (face->height + face->ascender + face->descender) >> 6;
	return (size);
}

/*
** ========================================================================== **
** Font management
*/
Canvas::font_t	Canvas::getFont(std::string const &file)
{
	auto const			&it = g_faces_cache.find(file);

	if (!g_freetype_init)
	{
		if (FT_Init_FreeType(&g_freetype))
			throw std::runtime_error("Cannot load FreeType library");
		g_freetype_init = true;
	}
	if (it != g_faces_cache.end())
		return (it->second);
	return (loadFont(file));
}

Canvas::font_t	Canvas::loadFont(std::string const &file)
{
	FT_Face				face;

	if (FT_New_Face(g_freetype, file.c_str(), 0, &face))
		throw std::runtime_error(ft::f("Cannot load %", file));
	g_faces.push_back(face);
	return (g_faces.size() - 1);
}

/*
** Changed Rect
*/
ft::Rect<int> const	&Canvas::getChangedRect(void) const
{
	return (_changedRect);
}

void				Canvas::resetChangedRect(void)
{
	_changedRect = ft::make_rect(0, 0, 0, 0);
}

void				Canvas::applyChangedRect(ft::Vec2<int> vec)
{
	if (_changedRect.left == _changedRect.right
		|| _changedRect.top == _changedRect.bottom)
	{
		_changedRect = ft::make_rect(vec.x, vec.y, vec.x + 1, vec.y + 1);
		std::cout << "reset changed rect " << _changedRect << std::endl;
	}
	else
		_changedRect.merge(vec);
}

void				Canvas::applyChangedRect(ft::Rect<int> const &rect)
{
	if (_changedRect.left == _changedRect.right
		|| _changedRect.top == _changedRect.bottom)
	{
		_changedRect = rect;
		std::cout << "reset changed rect " << _changedRect << std::endl;
	}
	else
		_changedRect.merge(rect);
}

};
