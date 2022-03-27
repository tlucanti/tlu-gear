/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:19:56 by tlucanti          #+#    #+#             */
/*   Updated: 2022/03/27 17:57:58 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TLUlanguage.h"

TLUobject int_sum(TLUobject a, TLUobject b)
{
    TLUfun_begin;
    TLUobject s = sum(a, b);
    TLUreturn(s);
}

int main()
{
    TLUinit;

    TLUobject   a  = num(123);
    TLUobject   b  = num(456);
    TLUobject   c  = num(789);
    TLUobject   sm = sum(a, b, c);

    print(TLUstr("sum of"), a, c, TLUstr("and"), b, TLUstr("="), sm);

    TLUobject   s1 = TLUstr("hello-");
    TLUobject   s2 = TLUstr("world");
    TLUobject   ss = TLUstr("");
    iadd(ss, s1);
    iadd(ss, s2);

    print(TLUstr("sum of"), s1, TLUstr("and"), s2, TLUstr("is"), ss);

    TLUstop;
}
