/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VerticalLayout.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:43 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/24 07:19:32 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTICALLAYOUT_HPP
# define VERTICALLAYOUT_HPP

# include "ALayout.hpp"
# include "IViewHolder.hpp"

class	VerticalLayout : public ALayout
{
public:
	// * NESTED OBJECTS ************* //
	class	ViewHolder : public IViewHolder
	{
	public:
		ViewHolder();
		virtual ~ViewHolder();

		virtual Vec2<int>	getPos(void) const;
		virtual Vec2<int>	getSize(void) const;

	private:
		ViewHolder(ViewHolder const &src);
		ViewHolder			&operator=(ViewHolder const &rhs);		
	};

	// * CTORS / DTORS ************** //
	VerticalLayout(void);
	virtual ~VerticalLayout(void);

protected:

private:
	VerticalLayout(VerticalLayout const &src);
	VerticalLayout			&operator=(VerticalLayout const &rhs);
};

#endif
