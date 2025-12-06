NAME = weekend_c

CC = cc
CFLAG = -Wall -Wextra -Werror $(patsubst %,-I%,$(INCDIRS))
RMDIR = rm -rf

SRCDIR = src

SRCFILES =	main.c \
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
			lambertian.c \

SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))

OBJDIR = obj

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

INCDIRS = $(MLXDIR) include

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
	$(CC) $(CFLAG) $(OBJS) $(LDLIBS)  -o $@

$(MLX):
	@$(MAKE) -C $(MLXDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

clean:
	@$(RMDIR) $(OBJDIR)
	@$(MAKE) -C $(MLXDIR) clean

fclean: clean
	@$(RM) $(NAME)

re: fclean all

# --- DEBUGGING & TESTING ---
lldb: fclean
	@$(MAKE) CFLAG="$(CFLAG) $(DFLAGS)" $(NAME)
	@echo "\n\033[1;35mLaunching LLDB for '$(NAME)'...\033[0m"
	@lldb $(NAME)

asan: fclean
	@$(MAKE) CFLAG="$(CFLAG) $(ASAN_FLAGS)" LDFLAGS="$(ASAN_FLAGS)" $(NAME)
	@echo "\n\033[1;35mCompiled with AddressSanitizer. Run './$(NAME)' to test.\033[0m"

valgrind: fclean
	@$(MAKE) CFLAG="$(CFLAG) $(DFLAGS)" $(NAME)
	@echo "\n\033[1;36mRunning Valgrind for '$(NAME)'...\033[0m"
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME)

test: all
	@$(MAKE) all
	@echo "\033[1;36mRunning tests with Valgrind...\033[0m"
	@$(CC) $(CFLAG) test.c $(NAME) -o test_runner
	$(VALGRIND) $(VALGRIND_FLAGS) ./test_runner
	@$(RM) test_runner

scanb: fclean
	@$(SCAN_BUILD) $(MAKE) all

# --- PHONY TARGETS ---
.PHONY:         all clean fclean re test debug asan valgrind
