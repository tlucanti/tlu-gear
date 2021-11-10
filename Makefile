# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kostya <kostya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 15:29:59 by kostya            #+#    #+#              #
#    Updated: 2021/11/10 23:31:23 by kostya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =============================== TESTER OPRIONS ===============================
C_DEFINES	=

# ------------------------------ NOVERBOSE ------------------------------
# uncomment this flag if you dont want to see where in tests are errors acure

# C_DEFINES	+=	-D NOVERBOSE

# ------------------------------ SILENT ------------------------------
# uncomment this flag if you dont want see any error messages, only result
#  of testing

# C_DEFINES	+=	-D SILENT

# ------------------------------ SILENT ------------------------------
# uncomment this flag if you want to stop program at first ocured error

C_DEFINES	+=	-D STOPATERROR

# ================================ COMPILE STUFF ===============================
# ------------------------------ compiler options ------------------------------
NAME		=	libTLU.a
NAME32		=	libTLU32.a
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror
COPTIONS	=	-O3 -ffast-math
AR			=	ar rc
# ------------------------------- linker options -------------------------------
LIBRARY		=	
OBJS_DIR	=	obj
OBJS_DIR32	=	obj32
INCLUDE_DIR	=	inc
SCRS_DIR	=	src
SCRS_DIR32	=	src32
GNL			=	gnl
TEST_DIR	=	test
# ------------------------------- project sorces -------------------------------
SRCS		=	\
				TLUmemset	\
				TLUbzero
SRCS32		=	\
				TLUmemset32
# ------------------------------------------------------------------------------
HDRS		=	\
				libTLU

# ======================= UNCHANGEABLE PART OF MAKEFILE ========================
# ------------------------------------------------------------------------------
RM			=	rm -f
OBJS		=	$(addprefix ${OBJS_DIR}/,${SRCS:=.o})
OBJS32		=	$(addprefix ${OBJS_DIR32}/,${SRCS32:=.o})
DEPS		=	$(addprefix ${INCLUDE_DIR}/,${HDRS:=.h})
INCLUDE		=	-I ${INCLUDE_DIR}

# ------------------------------------------------------------------------------
# all ${OBJS_DIR} ${OBJS_DIR32}:
all:
	@$(MAKE)	$(NAME) -j
	@$(MAKE)	$(NAME32) -j

# ------------------------------------------------------------------------------
${OBJS_DIR}/%.o: ${SCRS_DIR}/%.c ${DEPS} Makefile
	${CC}		${CFLAGS} ${COPTIONS} -c -o $@ $< ${INCLUDE}

${OBJS_DIR32}/%.o: ${SCRS_DIR32}/%.c ${DEPS} Makefile
	${CC}		${CFLAGS} ${COPTIONS} -m32 -c -o $@ $< ${INCLUDE}

# ------------------------------------------------------------------------------
$(NAME):		${OBJS} ${DEPS}
	${AR}		-o ${NAME} ${OBJS} ${LIBRARY}

# ------------------------------------------------------------------------------
$(NAME32):		${OBJS32} ${DEPS}
	${AR}		-o ${NAME32} ${OBJS32} ${LIBRARY}

# ------------------------------------------------------------------------------
clean:
	${RM}		${OBJS}
	${RM}		${OBJS32}

# ------------------------------------------------------------------------------
fclean:			clean
	${RM}		${NAME}
	${RM}		${NAME32}

# ------------------------------------------------------------------------------
re:				fclean install all

# ------------------------------------------------------------------------------
${OBJS_DIR}:
	mkdir		-p ${OBJS_DIR}

# ------------------------------------------------------------------------------
${OBJS_DIR32}:
	mkdir		-p ${OBJS_DIR32}

# =========================== TESTS PART OF MAKEFILE ===========================
# ------------------------------------------------------------------------------

test-%: all
	python3 ${TEST_DIR}/test_runner.py $@ '${C_DEFINES}'

# ------------------------------------------------------------------------------
.PHONY:			all clean fclean re
