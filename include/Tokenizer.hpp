// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tokenizer.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/17 16:47:01 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/18 17:25:41 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TOKENIZER_HPP
# define TOKENIZER_HPP

# include <istream>
# include <sstream>

/*
** TODO: improve
*/

class	Tokenizer
{
public:
	enum token_def_e
	{
		// Token of 1 char that is in 'data.str'
		TOKEN_CHR1,
		// Token that each char are in 'data.str'
		TOKEN_CHR,
		// Token of 1 char that applied to 'data.f' is true
		TOKEN_F1,
		// Token that each char applied to 'data.f' are true
		TOKEN_F
	};
	union token_data_u
	{
		char const		*str;
		int				(*f)(int c);
	};
	struct token_def_s
	{
		token_data_u	data;
		token_def_e		token_type;
		int				id;
	};

	Tokenizer(token_def_s const *defs, int def_count);
	virtual ~Tokenizer(void);

	/*
	** Return the last extracted token
	*/
	std::string			getToken(void) const;

	/*
	** Return the last extracted token type
	*/
	int					getTokenId(void) const;

	/*
	** Try to extract a token
	** Return true on success and false on error (or EOF)
	*/
	bool				next(std::istream &in);

protected:

	token_def_s const	*_defs;
	int					_def_count;

	std::ostringstream	_token;
	int					_tokenId;

private:
	Tokenizer(void);
	Tokenizer(Tokenizer const &src);
	Tokenizer			&operator=(Tokenizer const &rhs);
};

#endif
