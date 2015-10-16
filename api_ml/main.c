/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 11:16:56 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/16 14:54:32 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ========================================================================== **
** Ocaml -> C
*/

/*
** c functions
*/

#include <stdio.h>

int				g_lol_table[256] = {0};
int				g_lol_index = 0;

int				c_create_lol(int n)
{
	if (g_lol_index >= 255)
		return (-1);
	g_lol_table[g_lol_index] = n;
	return (g_lol_index++);
}

int				c_get_lol(int lol, int *dst)
{
	if (lol < 0 || lol >= g_lol_index)
		return (0);
	*dst = g_lol_table[lol];
	return (1);
}

int				c_set_lol(int lol, int v)
{
	if (lol < 0 || lol >= g_lol_index)
		return (0);
	g_lol_table[lol] = v;
	return (1);
}

void			c_print_lol(int lol)
{
	printf("%d", lol);
	fflush(stdout);
}

/*
** hooks
*/

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/fail.h>

CAMLprim value	hook_create_lol(value mdr)
{
	int				lol;

	CAMLparam1(mdr);
	lol = c_create_lol(Long_val(mdr));
	if (lol < 0)
		caml_raise_with_string(*caml_named_value("lol_error"), "No more lol available");
	CAMLreturn(Val_long(lol));
}

CAMLprim value	hook_get_lol(value mdr)
{
	int				lol;

	CAMLparam1(mdr);
	if (!c_get_lol(Long_val(mdr), &lol))
		caml_raise_with_string(*caml_named_value("lol_error"), "Invalid lol");
	CAMLreturn(Val_long(lol));
}

CAMLprim value	hook_set_lol(value mdr, value v)
{
	int				lol;

	CAMLparam2(mdr, v);
	if (!c_set_lol(Long_val(mdr), Long_val(v)))
		caml_raise_with_string(*caml_named_value("lol_error"), "Invalid lol");
	CAMLreturn(Val_unit);
}

CAMLprim value	hook_bad_lol(void)
{
	CAMLparam0();
	CAMLreturn(Val_long(1000));
}

CAMLprim value	hook_print_lol(value mdr)
{
	CAMLparam1(mdr);
	c_print_lol(Long_val(mdr));
	CAMLreturn(Val_unit);
}

/*
** ========================================================================== **
** C to Ocaml
*/

void			test_lol(void)
{
	value *const	do_lol = caml_named_value("do_lol");

	if (do_lol == NULL)
	{
		printf("Error: do_lol not found\n");
		return ;
	}
	caml_callback(*do_lol, Val_long(5));
	caml_callback(*do_lol, Val_long(10));
	caml_callback(*do_lol, Val_long(0));
	caml_callback(*do_lol, Val_long(-1));
	caml_callback(*do_lol, Val_long(42));
}

/*
** ========================================================================== **
*/

int				main(int argc, char **argv)
{
	caml_startup(argv); // Start ocaml's main ('let () =')
	test_lol();
	return (0);
}
