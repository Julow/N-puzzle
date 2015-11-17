// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tokenizer.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/17 17:07:25 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/17 20:16:52 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Tokenizer.hpp"
#include "ft/utils.hpp"

Tokenizer::Tokenizer(token_def_s const *defs, int def_count) :
	_defs(defs),
	_def_count(def_count)
{
}

Tokenizer::~Tokenizer(void)
{
}

std::string			Tokenizer::getToken(void) const
{
	return (_token.str());
}

int					Tokenizer::getTokenId(void) const
{
	return (_tokenId);
}

bool				Tokenizer::next(std::istream &in)
{
	char				c;

	_token.str("");
	c = in.peek();
	if (in.eof())
		return (false);
	_token.put(c);
	for (int i = 0; i < _def_count; i++)
	{
		token_def_s const	*def = _defs + i;

		switch (def->token_type)
		{
		case TOKEN_CHR1:
		case TOKEN_CHR:
			if (std::strchr(def->data.str, c) == NULL)
				break ;
			in.get();
			if (def->token_type == TOKEN_CHR)
				while (true)
				{
					c = in.peek();
					if (std::strchr(def->data.str, c) == NULL)
						break ;
					_token.put(in.get());
				}
			_tokenId = def->id;
			return (true);
		case TOKEN_F1:
		case TOKEN_F:
			if (!def->data.f(c))
				break ;
			in.get();
			if (def->token_type == TOKEN_F)
				while (true)
				{
					c = in.peek();
					if (!def->data.f(c))
						break ;
					_token.put(in.get());
				}
			_tokenId = def->id;
			return (true);
		}
	}
	return (false);
}
