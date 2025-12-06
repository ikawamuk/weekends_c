NAME = weekend_c

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE)
RMDIR	= rm -rf

SRCS	=	main.c \
			draw_image.c \
			img.c \
			vec3.c \
			color.c \
			ray.c \
			sphere.c \
			hit_table_list.c \
			camera.c \
			util.c \
			ray_color.c \

OBJDIR = obj

OBJS	= $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))


INCLUDE = $(MLXDIR)

MLXDIR = minilibx-linux
MLX = $(MLXDIR)/mlx.a

LDLIBS = -L./minilibx-linux -lmlx -lX11 -lXext -lm

# --- DEBUGGING ---
VALGRIND        = valgrind
VALGRIND_FLAGS  = --leak-check=full --track-origins=yes --show-leak-kinds=all
DFLAGS          = -g -O0
ASAN_FLAGS      = -g -fsanitize=address
SCAN_BUILD      = scan-build

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS)  -o $@

$(MLX):
	@MAKEFLAGS= $(MAKE) -C $(MLXDIR)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RMDIR) $(OBJDIR)
	@MAKEFLAGS= $(MAKE) -C $(MLXDIR) clean

fclean: clean
	@$(RM) $(NAME)

re: fclean all

# --- DEBUGGING & TESTING ---
lldb: fclean
	@$(MAKE) CFLAGS="$(CFLAGS) $(DFLAGS)" $(NAME)
	@echo "\n\033[1;35mLaunching LLDB for '$(NAME)'...\033[0m"
	@lldb $(NAME)

asan: fclean
	@$(MAKE) CFLAGS="$(CFLAGS) $(ASAN_FLAGS)" LDFLAGS="$(ASAN_FLAGS)" $(NAME)
	@echo "\n\033[1;35mCompiled with AddressSanitizer. Run './$(NAME)' to test.\033[0m"

valgrind: fclean
	@$(MAKE) CFLAGS="$(CFLAGS) $(DFLAGS)" $(NAME)
	@echo "\n\033[1;36mRunning Valgrind for '$(NAME)'...\033[0m"
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME)

test: all
	@$(MAKE) all
	@echo "\033[1;36mRunning tests with Valgrind...\033[0m"
	@$(CC) $(CFLAGS) test.c $(NAME) -o test_runner
	$(VALGRIND) $(VALGRIND_FLAGS) ./test_runner
	@$(RM) test_runner

scanb: fclean
	@$(SCAN_BUILD) $(MAKE) all

# --- PHONY TARGETS ---
.PHONY:         all clean fclean re test debug asan valgrind
