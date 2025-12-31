NAME = weekend_c

CC = cc 

CFLAG = -Wall -Wextra -Werror $(patsubst %,-I%,$(INCDIRS)) -I$(MLXDIR) -I$(LIBFTDIR)/includes -O3 -march=native
RMDIR = rm -rf

SRCDIR = src

SRCFILES =		main.c \
				mini_rt.c \
				draw.c \
				img.c \
				vec3.c \
				color.c \
				ray.c \
				cylinder.c \
				sphere.c \
				plane.c \
				cone.c \
				hit_table.c \
				hit_table_list.c \
				get_object.c \
				camera.c \
				rt_utils.c \
				ray_color.c \
				material.c \
				lambertian.c \
				metal.c \
				light.c \
				dielectric.c \
				set_world.c \
				cosine_pdf.c \
				light_pdf.c \
				mixture_pdf.c \
				solid_texture.c \
				checker_texture.c \
				validate.c \
				validate_ambient.c \
				validate_camera.c \
				validate_cylinder.c \
				validate_plane.c \
				validate_sphere.c \
				validate_light.c \
				validate_cone.c \
				bvh.c \
				range.c \
				set_object.c \
				set_light.c \
				aabb.c \
				phong.c \


SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))

OBJDIR = obj

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

INCDIRS = include

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

# --- OS DETECTION ---
UNAME = $(shell uname -s)

ifeq ($(UNAME),Darwin)
	MLXDIR := $(HOME)/minilibx
	MLX_FLAGS := -framework OpenGL -framework AppKit
else ifeq ($(UNAME),Linux)
	MLXDIR := minilibx-linux
	MLX_FLAGS := -lX11 -lXext
else
	$(error Unsupported OS: $(UNAME))
endif

MLX = $(MLXDIR)/libmlx.a

LDFLAGS = -L $(MLXDIR)
LDLIBS = -lmlx -lm $(MLX_FLAGS)


# --- DEBUGGING ---
VALGRIND		= valgrind
VALGRIND_FLAGS	= --leak-check=full --track-origins=yes --show-leak-kinds=all
DFLAGS			= -g -O0
ASAN_FLAGS		= -g -fsanitize=address
SCAN_BUILD		= scan-build

# --- test ---
TESTNAME= test_weekend_c

TESTCFlAGS = $(CFLAG) -g -O0 -I$(INCDIRS)/test/ -Wl,--wrap=open,--wrap=read,--wrap=malloc,--wrap=free

TESTSRCFILES =	$(addprefix test/, \
				test.c \
				$(addprefix unit_tests/, \
				syscall_mock.c \
				$(addprefix test_set_world/, \
				test_set_world.c \
				test_check_file_name.c \
				test_read_rt.c \
				$(addprefix test_validate/, \
				test_validate.c \
				test_validate_ambient.c \
				))))

TESTSRCS = $(addprefix $(SRCDIR)/, $(TESTSRCFILES))
TESTOBJS = $(filter-out $(OBJDIR)/main.o, $(OBJS)) $(TESTSRCS)

# --- Rules ---

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAG) $(OBJS) $(LIBFT) $(LDFLAGS) $(LDLIBS) -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) bonus

$(MLX):
	@$(MAKE) -C $(MLXDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

clean:
	@$(RMDIR) $(OBJDIR)
# @$(MAKE) -C $(LIBFTDIR) fclean
# @$(MAKE) -C $(MLXDIR) clean

fclean: clean
	@$(RM) $(NAME) $(TESTNAME)

re: fclean all

# --- DEBUGGING & TESTING ---
lldb: fclean
	@$(MAKE) CFLAG="$(CFLAG) $(DFLAGS)" $(NAME)
	@echo "\n\033[1;35mLaunching LLDB for '$(NAME)'...\033[0m"
	@lldb $(NAME)

asan: fclean
	@$(MAKE) CFLAG="$(CFLAG) $(ASAN_FLAGS)" LDFLAGS="$(LDFLAGS) $(ASAN_FLAGS)" $(NAME)
	@echo "\n\033[1;35mCompiled with AddressSanitizer. Run './$(NAME)' to test.\033[0m"

valgrind: fclean
	@$(MAKE) CFLAG="$(CFLAG) $(DFLAGS)" $(NAME)
	@echo "\n\033[1;36mRunning Valgrind for '$(NAME)'...\033[0m"
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME)

test: re
	@$(RM) $(NAME)
	@$(MAKE) $(TESTNAME)

$(TESTNAME):$(OBJS) $(MLX) $(LIBFT)
	$(CC) $(TESTCFlAGS) $(TESTOBJS) $(LIBFT) $(LDFLAGS) $(LDLIBS) -o $@

scanb: fclean
	@$(SCAN_BUILD) $(MAKE) all

# --- PHONY TARGETS ---
.PHONY:		all clean fclean re test debug asan valgrind scanb