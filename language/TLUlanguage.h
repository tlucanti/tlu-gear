/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TLUlanguage.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:56:58 by tlucanti          #+#    #+#             */
/*   Updated: 2022/03/27 17:57:38 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TLU_LANGUAGE_H
# define __TLU_LANGUAGE_H

# ifdef __ALLOC_DEBUG
#  define __alloc_log printf
# else
#  define __alloc_log(...)
# endif /* __ALLOC_DEBUG */

# include "inc/TLUdefs.h"
# include "inc/TLUobject.h"
# include "inc/TLUnum.h"
# include "inc/TLUstr.h"
# include "inc/TLUbuiltin.h"

#endif /* __TLU_LANGUAGE_H */
