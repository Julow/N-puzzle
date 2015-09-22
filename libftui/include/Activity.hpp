/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:16:33 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/22 15:26:18 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIVITY_HPP
# define ACTIVITY_HPP

# include <vector>
# include <unordered_map>
# include <string>
# include "ACanvas.hpp"
# include "AView.hpp"

class	Activity
{
public:
	typedef std::unordered_multimap<std::string, AView*>	event_map_t;

	Activity(void);
	virtual ~Activity(void);

	void			inflate(std::string const &xml);
	void			loadScripts(std::vector<std::string> const &scripts);

	bool			onDraw(ACanvas &canvas);

	void			onKeyUp(int key_code);
	bool			onKeyDown(int key_code);

	void			onMouseMove(int x, int y);

	void			onMouseUp(void);
	bool			onMouseDown(int x, int y);

	bool			fireEvent(std::string const &event);

protected:

	AView			*_view;

	event_map_t		_eventMap;

private:
	Activity(Activity const &src);
	Activity		&operator=(Activity const &rhs);
};

#endif
