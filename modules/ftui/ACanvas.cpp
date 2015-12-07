// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ACanvas.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:22 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/07 14:33:50 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

extern "C"
{
#include <ft2build.h>
#include FT_FREETYPE_H
}

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
// #include <cfenv>

#include "ft/utils.hpp"
#include "ftlua/stackassert.hpp"
#include "ftlua/ftlua.hpp"

#include "ftui/ACanvas.hpp"

#define DEFAULT_FONT		RES_PATH "/fonts/Arial_Black.ttf"

namespace ftui
{

/*
** Globals used to manage fonts
*/
static FT_Library			g_freetype;
static bool					g_freetype_init = false;
static std::unordered_map<std::string, ACanvas::font_t> g_faces_cache;
static std::vector<FT_Face>	g_faces;

/*
** Construction
*/

ACanvas::ACanvas(int width, int height) :
	_width(width),
	_height(height),
	_clip(0, 0, width, height),
	_alpha(1.f),
	_scale(1.f),
	_luaFont(0)
{
	resetChangedRect();
	initFonts();
	return ;
}

ACanvas::~ACanvas(void)
{
	return ;
}

/*
** ========================================================================== **
** LUA Interations
*/

int				ACanvas::drawRectG(lua_State *l)
{
	ACanvas *const		self = ftlua::pop<ACanvas*>(l, 1);
	// ACanvas *const		self = ftlua::retrieveSelf<ACanvas>(l, 1);
	ACanvas::Params		p;
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
	FTLUA_STACKASSERT(l, top <= 7, true
					  , "ACanvas::drawRectG"
					  , "Too many arguments");
	self->drawRect(r, p);
	return (0);
}

int				ACanvas::drawTextG(lua_State *l)
{
	ACanvas *const		self = ftlua::pop<ACanvas*>(l, 1);
	// ACanvas *const		self = ftlua::retrieveSelf<ACanvas>(l, 1);
	ACanvas::Params		params;
	ft::Vec2<float>		pos;
	std::string			text;
	int const			top = lua_gettop(l);

	text = luaL_checkstring(l, 1);
	pos.x = luaL_checknumber(l, 2);
	pos.y = luaL_checknumber(l, 3);
	params.fillColor = luaL_checkinteger(l, 4);
	params.lineWidth = luaL_checkinteger(l, 5);
	params.font = self->_luaFont;
	FTLUA_STACKASSERT(l, top <= 5, true
					  , "ACanvas::drawTextG"
					  , "Too many arguments");
	self->drawText(pos, text, params);
	return (0);
}

int				ACanvas::setFontG(lua_State *l)
{
	ACanvas *const		self = ftlua::pop<ACanvas*>(l, 1);
	// ACanvas *const		self = ftlua::retrieveSelf<ACanvas>(l, 1);

	self->_luaFont = ACanvas::getFont(luaL_checkstring(l, 1));
	return (0);
}

int				ACanvas::measureTextG(lua_State *l)
{
	ACanvas *const		self = ftlua::pop<ACanvas*>(l, 1);
	// ACanvas *const		self = ftlua::retrieveSelf<ACanvas>(l, 1);
	std::string			text;
	ACanvas::Params		params;

	text = luaL_checkstring(l, 1);
	params.lineWidth = luaL_checkinteger(l, 2);
	params.font = self->_luaFont;
	lua_pop(l, lua_gettop(l));
	ftlua::push(l, self->measureText(text, params));
	return 2;
}

void			ACanvas::pushTemplate(lua_State *l)
{
	luaL_dostring(l, "ACanvas = {}; ACanvas.__index = ACanvas;");
	ftlua::set(l, ftlua::makeKeys("ACanvas"), "drawRect", &ACanvas::drawRectG);
	ftlua::set(l, ftlua::makeKeys("ACanvas"), "drawText", &ACanvas::drawTextG);
	ftlua::set(l, ftlua::makeKeys("ACanvas"), "measureText"
			   , &ACanvas::measureTextG);
	ftlua::set(l, ftlua::makeKeys("ACanvas"), "setFont", &ACanvas::setFontG);
	return ;
}

void			ACanvas::pushLua(lua_State *l)
{
	ftlua::multiPush(l, ftlua::newtab, ftlua::makeKeys("ACanvas"));
	FTLUA_STACKASSERT(l, lua_istable(l, -1), false
					  , "ACanvas::pushLua", "Could not retreive _G['ACanvas']");
	lua_setmetatable(l, -2);
	ftlua::set(l, -1, 0, ftlua::light(this));
	ftlua::set(l, ftlua::light(this), ftlua::dup(-3));
	lua_pop(l, 1);
	return ;
}

bool			ACanvas::isInLua(lua_State *l)
{
	ftlua::pushLightKey(l, this);
	if (!lua_istable(l, -1))
	{
		lua_pop(l, 1);
		return false;
	}
	lua_pop(l, 1);
	return true;
}
void				ACanvas::ftlua_push(lua_State *l,
						std::function<void(std::string)> panic)
{
	ftlua::pushLightKey(l, this);
	FTLUA_STACKASSERT_PANIC(
		l, lua_istable(l, -1), panic
		, ft::f("ACanvas::ftlua_push()"), ft::f("_G[this] not found."));
	return ;
}

ACanvas				*ACanvas::ftlua_pop(lua_State *l, int i,
						std::function<void(std::string)> panic)
{
	ACanvas		*v;
	int			type;

	FTLUA_STACKASSERT_PANIC(
		l, lua_istable(l, i), panic
		, ft::f("ACanvas::ftlua_pop(i = %)", i), ft::f("No table at i"));
	ftlua::push(l, 0);
	type = lua_gettable(l, i < 0 ? i - 1 : i);
	FTLUA_STACKASSERT_PANIC(
		l, type == LUA_TLIGHTUSERDATA, panic
		, ft::f("ACanvas::ftlua_pop(i = %)", i), ft::f("No pointer at [0]"));
	v = reinterpret_cast<ACanvas*>(lua_touserdata(l, -1));
	lua_pop(l, 1);
	lua_remove(l, i);
	return v;
}

/*
** ========================================================================== **
** Origin
*/

void			ACanvas::setOrigin(ft::Vec2<int> origin)
{
	_origin = origin;
}

void			ACanvas::applyOrigin(ft::Vec2<int> apply)
{
	_origin += apply;
}

ft::Vec2<int>	ACanvas::getOrigin(void) const
{
	return (_origin);
}

/*
** ========================================================================== **
** Scale
*/
void			ACanvas::setScale(float scale)
{
	_scale = scale;
}

float			ACanvas::getScale(void) const
{
	return (_scale);
}

/*
** ========================================================================== **
** Clip
*/
ft::Rect<int>	ACanvas::getClip(void) const
{
	return (_clip - _origin);
}

void			ACanvas::setClip(ft::Rect<int> const &clip)
{
	_clip = clip;
	_clip += _origin;
}

void			ACanvas::setClip(ft::Vec2<int> size)
{
	_clip.setPos(_origin);
	_clip.setSize(size);
}

void			ACanvas::clearClip(void)
{
	clear(_clip);
}

/*
** ========================================================================== **
** Alpha
*/
float			ACanvas::getAlpha(void) const
{
	return (_alpha);
}

void			ACanvas::applyAlpha(float alpha)
{
	_alpha *= alpha;
}

void			ACanvas::setAlpha(float alpha)
{
	_alpha = alpha;
}

/*
** ========================================================================== **
** Render rect
*/
void			ACanvas::drawRect(ft::Rect<float> const &rect, Params const &opt)
{
	ft::Rect<int>	int_rect = static_cast<ft::Rect<int>>(rect * _scale);

	int_rect += _origin;
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

/*
** ========================================================================== **
** Render text
*/
void			ACanvas::drawText(ft::Vec2<float> pos, std::string const &text,
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
	applyChangedRect(int_vec);
	face = g_faces[opt.font];
	if (FT_Set_Pixel_Sizes(face, 0, opt.lineWidth))
		throw std::runtime_error("ACanvas::drawText: "
								 "Cannot resize font (drawText)");
	if (int_vec.y >= _clip.bottom)
		return ;
	int_vec.y += opt.lineWidth;
	if (int_vec.y < _clip.top)
		return ;
	// int_vec.y += (face->descender * 2 + face->height + face->ascender) >> 6;
	// TODO: Fix les font height please
	for (uint32_t i = 0; i < text.size(); i++)
	{
		if (int_vec.x >= _clip.right)
			break ;
		glyph_index = FT_Get_Char_Index(face, text[i]);
		if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
			continue ;
		if ((int_vec.x + (face->glyph->advance.x >> 6)) > _clip.left)
		{
			if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
				continue ;
			glyph_rect.right = face->glyph->bitmap.width;
			glyph_rect.bottom = face->glyph->bitmap.rows;
			_putAlphaBitmap(int_vec
				+ ft::make_vec(face->glyph->bitmap_left, -face->glyph->bitmap_top),
				face->glyph->bitmap.buffer, glyph_rect, face->glyph->bitmap.pitch,
						   opt.fillColor);
		}
		int_vec.x += face->glyph->advance.x >> 6;
	}
	applyChangedRect(int_vec);
	return ;
}

ft::Vec2<int>	ACanvas::measureText(std::string const &text, Params const &opt)
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
		throw std::runtime_error("ACanvas::measureText: "
								 "Cannot resize font (measureText)");
	for (uint32_t i = 0; i < text.size(); i++)
	{
		glyph_index = FT_Get_Char_Index(face, text[i]);
		if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
			continue ;
		size.x += face->glyph->advance.x;
	}
	size.x >>= 6;
	// TODO: Fix les font height please
	size.y = opt.lineWidth;
	return (size);
}

/*
** ========================================================================== **
** Font management
*/
void			ACanvas::initFonts(void)
{
	if (g_freetype_init)
		return ;
	if (FT_Init_FreeType(&g_freetype))
		throw std::runtime_error("ACanvas::getFont: "
								 "Cannot load FreeType library");
	g_freetype_init = true;
	loadFont(DEFAULT_FONT);
	FTASSERT(g_faces.size() == 1);
}

ACanvas::font_t	ACanvas::getFont(std::string const &file)
{
	auto const			&it = g_faces_cache.find(file);

	if (!g_freetype_init)
		initFonts();
	if (it != g_faces_cache.end())
		return (it->second);
	return (loadFont(file));
}

ACanvas::font_t	ACanvas::loadFont(std::string const &file)
{
	FT_Face				face;

	if (FT_New_Face(g_freetype, file.c_str(), 0, &face))
		throw std::runtime_error(ft::f("ACanvas::loadFont: "
									   "Cannot load %", file));
	g_faces.push_back(face);
	return (g_faces.size() - 1);
}

/*
** Changed Rect
*/
ft::Rect<int> const	&ACanvas::getChangedRect(void) const
{
	return (_changedRect);
}

void				ACanvas::resetChangedRect(void)
{
	_changedRect = ft::make_rect(0, 0, 0, 0);
}

void				ACanvas::applyChangedRect(ft::Vec2<int> vec)
{
	if (_changedRect.left == _changedRect.right
		|| _changedRect.top == _changedRect.bottom)
	{
		_changedRect = ft::make_rect(vec.x, vec.y, vec.x + 1, vec.y + 1);
	}
	else
		_changedRect.merge(vec);
}

void				ACanvas::applyChangedRect(ft::Rect<int> const &rect)
{
	if (_changedRect.left == _changedRect.right
		|| _changedRect.top == _changedRect.bottom)
	{
		_changedRect = rect;
	}
	else
		_changedRect.merge(rect);
}

};
