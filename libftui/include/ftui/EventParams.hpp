/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventParams.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 09:44:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/10/02 10:25:18 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTPARAMS_HPP
# define EVENTPARAMS_HPP

# include "ftui/IEventParams.hpp"

# include <tuple>

template<typename... ARGS>
class ftui::EventParams : public IEventParams
{
public:
	EventParams() : tup() {};
	virtual ~EventParams();

	std::tuple<ARGS...>			tup;
private:
	EventParams(EventParams const &src) = delete;
	EventParams					&operator=(EventParams const &rhs) = delete;

};

#endif // *************************************************** EVENTPARAMS_HPP //
