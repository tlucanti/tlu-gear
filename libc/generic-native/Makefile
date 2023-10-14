
FUNCS = bzero  isdigit  memcmp  memeq  memset
NAME = ../../build/libgeneric-slow.a
OBJ = $(addsuffix .o,$(FUNCS))

all: $(NAME)

%.o: %.c
	gcc -c $< -o $@

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	rm $(OBJ)
