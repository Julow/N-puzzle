// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   CheckBox.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/28 12:40:52 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/05 17:33:06 by ngoguey          ###   ########.fr       //
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

AView		*CheckBox::createView(ftui::Activity &act)
{
	return (new CheckBox(act));
}

CheckBox::CheckBox(Activity &act, std::string const &viewName)
	: Button(act, viewName)
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
	CheckBox  *v = ftlua::pop<CheckBox*>(l, 1);
	// CheckBox  *v = ftlua::retrieveSelf<CheckBox>(l, 1);

	v->setCheckedParams(CheckBox::retrieveParams(l));
	return 0;
}


ACanvas::Params const	&CheckBox::getDisabledCheckedParams(void) const
{ return this->_disabledChecked ; }

void				CheckBox::setDisabledCheckedParams(ACanvas::Params const &p)
{ this->_disabledChecked = p; }

int                     CheckBox::setDisabledCheckedParamsG(lua_State *l)
{
	CheckBox  *v = ftlua::pop<CheckBox*>(l, 1);
	// CheckBox  *v = ftlua::retrieveSelf<CheckBox>(l, 1);

	v->setDisabledCheckedParams(CheckBox::retrieveParams(l));
	return 0;
}

void                CheckBox::setParam(
	std::string const &k, std::string const &v)
{
	using lambda = void (*)(CheckBox*,std::string const&);
	using map = std::unordered_map<std::string, lambda>;

	static map		param_map
	{
		{"checked", [](CheckBox *v, std::string const &str) {
				v->setChecked(str == "true");
			}},
		{"checkedFillColor", [](CheckBox *v, std::string const &str) {
				auto old = v->getCheckedParams();
				old.fillColor = std::stoul(str, NULL, 16);
				v->setCheckedParams(old);
			}},
		{"checkedStrokeColor", [](CheckBox *v, std::string const &str) {
				auto old = v->getCheckedParams();
				old.strokeColor = std::stoul(str, NULL, 16);
				v->setCheckedParams(old);
			}},
		{"checkedBorderWidth", [](CheckBox *v, std::string const &str) {
				auto old = v->getCheckedParams();
				old.lineWidth = std::stoi(str, NULL);
				v->setCheckedParams(old);
			}},
			// {"checkedBorderWidth", [](CheckBox *v, std::string const &str) {
		// 		auto old = v->getCheckedParams();
		// 		old.lineWidth = std::stoi(str, NULL);
		// 		v->setCheckedParams(old);
		// 	}},
	};
	auto const      &it = param_map.find(k);

	if (it != param_map.end())
		it->second(this, v);
	else
		Button::setParam(k, v);
}

};
