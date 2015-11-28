// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   CheckBox.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/28 12:40:52 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/28 16:31:08 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/CheckBox.hpp"
#include "ftui/Activity.hpp"
#include "ftui/IViewHolder.hpp"

namespace ftui
{

/* ************************************************************************** **
** CONSTRUCTION
*/

AView		*CheckBox::createView(
	ftui::Activity &act, ft::XmlParser const *xml, std::string const *id)
{
	FTASSERT((xml == nullptr) != (id == nullptr));
	if (xml == nullptr)
		return new CheckBox(act, id);
	return new CheckBox(act, *xml);
}

CheckBox::CheckBox(Activity &act, ft::XmlParser const &xml)
	: Button(act, xml)
	, _isChecked(false)
	, _checked{ 0x01000000, 0xFFFFFF00, 9, 0}
	, _disabledChecked{	0, 0, 0, 0}
{
	return ;
}

CheckBox::CheckBox(Activity &act, std::string const *id
				   , std::string const &viewName /* = "CheckBox" */)
	: Button(act, id, viewName)
	, _isChecked(false)
	, _checked{ 0x01000000, 0xFFFFFF00, 9, 0}
	, _disabledChecked{	0, 0, 0, 0}
{
	return ;
}

CheckBox::~CheckBox()
{
	return ;
}

/* ************************************************************************** **
** DRAW
*/

void		CheckBox::onDraw(ACanvas &canvas)
{
	IViewHolder		*vh = this->getViewHolder();

	FTASSERT(vh != nullptr);
	Button::onDraw(canvas);
	if (_state && _isChecked)
		canvas.drawRect(ft::make_rect(ft::make_vec(0, 0), _holder->getSize()),
						_checked);
	else if (_isChecked)
		canvas.drawRect(ft::make_rect(ft::make_vec(0, 0), _holder->getSize()),
						_disabledChecked);
	return ;
}


/* ************************************************************************** **
** INTERACTIONS
*/

void		CheckBox::onClick(int mods)
{
	this->setChecked(_isChecked ? false : true);
	Button::onClick(mods);
	return ;
}

int          CheckBox::isCheckedG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 1>(l, &CheckBox::isChecked);
}
bool		CheckBox::isChecked(void) const
{
	return _isChecked;
}

int          CheckBox::setCheckedG(lua_State *l) /*static*/
{
	return ftlua::handle<2, 0>(l, &CheckBox::setChecked);
}
void		CheckBox::setChecked(bool b)
{
	if (_isChecked != b)
	{
		_isChecked = b;
		this->queryRedraw();
	}
	return ;
}



ACanvas::Params const	&CheckBox::getCheckedParams(void) const
{ return this->_checked ; }

void					CheckBox::setCheckedParams(ACanvas::Params const &p)
{ this->_checked = p; }
int                     CheckBox::setCheckedParamsG(lua_State *l)
{
	CheckBox  *v = ftlua::retrieveSelf<CheckBox>(l, 1);

	v->setCheckedParams(CheckBox::retrieveParams(l));
	return 0;
}


ACanvas::Params const	&CheckBox::getDisabledCheckedParams(void) const
{ return this->_disabledChecked ; }

void				CheckBox::setDisabledCheckedParams(ACanvas::Params const &p)
{ this->_disabledChecked = p; }

int                     CheckBox::setDisabledCheckedParamsG(lua_State *l)
{
	CheckBox  *v = ftlua::retrieveSelf<CheckBox>(l, 1);

	v->setDisabledCheckedParams(CheckBox::retrieveParams(l));
	return 0;
}
};
