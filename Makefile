NAME = minishell
NAME_BONUS = minishell_b

CC = cc
# FLAGS = -Wextra -Wall -g -fPIE -I$(HEADER_FOLDER)
FLAGS = -Wextra -Wall -Werror -g -fPIE -I$(HEADER_FOLDER)

all: $(NAME)

# ╭──────────────────────────────────────────────────────────────────────────────────────────────────────────────╮
# │─██████████████─██████████████─██████████████─██████████████─██████████─██████──────────██████─██████████████─│
# │─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░██─██░░██████████──██░░██─██░░░░░░░░░░██─│
# │─██████░░██████─██░░██████████─██░░██████████─██████░░██████─████░░████─██░░░░░░░░░░██──██░░██─██░░██████████─│
# │─────██░░██─────██░░██─────────██░░██─────────────██░░██───────██░░██───██░░██████░░██──██░░██─██░░██─────────│
# │─────██░░██─────██░░██████████─██░░██████████─────██░░██───────██░░██───██░░██──██░░██──██░░██─██░░██─────────│
# │─────██░░██─────██░░░░░░░░░░██─██░░░░░░░░░░██─────██░░██───────██░░██───██░░██──██░░██──██░░██─██░░██──██████─│
# │─────██░░██─────██░░██████████─██████████░░██─────██░░██───────██░░██───██░░██──██░░██──██░░██─██░░██──██░░██─│
# │─────██░░██─────██░░██─────────────────██░░██─────██░░██───────██░░██───██░░██──██░░██████░░██─██░░██──██░░██─│
# │─────██░░██─────██░░██████████─██████████░░██─────██░░██─────████░░████─██░░██──██░░░░░░░░░░██─██░░██████░░██─│
# │─────██░░██─────██░░░░░░░░░░██─██░░░░░░░░░░██─────██░░██─────██░░░░░░██─██░░██──██████████░░██─██░░░░░░░░░░██─│
# │─────██████─────██████████████─██████████████─────██████─────██████████─██████──────────██████─██████████████─│
# ╰──────────────────────────────────────────────────────────────────────────────────────────────────────────────╯


NAMEE = minishell
NAMEE_BONUS = minishell_b

# RUN MINISHELL
a: $(NAMEE) small_clean
	@$(call random_shmol_cat, teshting ... $@: minishell, 'hav fun ね? ($(word 1, $^))', $(CLS), );
	./$(word 1, $^)

# RUN MINISHELL & BASH TERMINAL
b: $(NAMEE) small_clean
	gnome-terminal -- bash --posix &
	@$(call random_shmol_cat, teshting ... $@: minishell, 'hav fun ね? ($(word 1, $^))', $(CLS), );
	./$(word 1, $^)

# RUN BASH
t:
	gnome-terminal -- bash --posix &

# RUN MINISHELL & VALGRING 2> out/valgrind
v: $(NAMEE) small_clean
	@$(call random_shmol_cat, "vlgrininnng ... $(word 1, $^)!", "$(ARG2)", $(CLS), );
	-$(VALGRIND) ./$(word 1, $^) 2> out/valgrind

# RUN TESTS IN data/TESTS UNTIL EMPTY LINE
# RUN MINISHELL & VALGRING 2> out/valgrind
m: $(NAMEE) small_clean
	@while IFS= read -r line; do \
		if [ -z "$$line" ]; then break; fi; \
		$(call random_shmol_cat, "teshiing ... $(word 1, $^)!", "$$line", $(CLS), ); \
		echo "$(C_1R_4G_1B) \tBASH:$(RESET)"; \
		bash --posix -c "$$line" < /dev/tty; \
		echo "$(C_4R_1G_1B) \tMINISHELL:$(RESET)"; \
		$(VALGRIND) ./$(word 1, $^) -c "$$line" < /dev/tty 2> out/valgrind; \
		echo "\t$(C_1R_4G_1B)~ Press Enter to continue...$(RESET)"; read -p "" key < /dev/tty; \
	done < data/TESTS

# CHECK FD
maieul: $(NAMEE) small_clean
	@$(call random_shmol_cat, "teshiing ... $(word 1, $^)!", "lets find tis fd", $(CLS), )
	@if [ ! -e traces ]; then \
		mkdir -p traces; \
	fi; \
	strace -e dup2,dup,openat,clone,read,write,access,close,execve,pipe,pipe2 -tt -ff -o traces/trace \
	./minishell -c "sleep 50 | sleep 50 | sleep 50"; \
	strace-log-merge traces/trace | batcat -lstrace;

small_clean:
	-@rm -rf ./out traces
	@if [ ! -e out ]; then \
		mkdir -p out; \
	fi;

ULIMIT = 3000
m2: $(NAMEE)
	@$(call random_shmol_cat, "\'trying to make shit crash", "try n break it.. にゃ?", $(CLS), );
	@(ulimit -s $(ULIMIT); ./$(word 1, $^) $(ARG))
	ulimit -s 8192


# ╭──────────────────────────────────────────────────────────────────────────────────────────────────────────────╮
# │─██████████████─██████████████─██████──██████─████████████████───██████████████─██████████████─██████████████─│
# │─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░██──██░░██─██░░░░░░░░░░░░██───██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─│
# │─██░░██████████─██░░██████░░██─██░░██──██░░██─██░░████████░░██───██░░██████████─██░░██████████─██░░██████████─│
# │─██░░██─────────██░░██──██░░██─██░░██──██░░██─██░░██────██░░██───██░░██─────────██░░██─────────██░░██─────────│
# │─██░░██████████─██░░██──██░░██─██░░██──██░░██─██░░████████░░██───██░░██─────────██░░██████████─██░░██████████─│
# │─██░░░░░░░░░░██─██░░██──██░░██─██░░██──██░░██─██░░░░░░░░░░░░██───██░░██─────────██░░░░░░░░░░██─██░░░░░░░░░░██─│
# │─██████████░░██─██░░██──██░░██─██░░██──██░░██─██░░██████░░████───██░░██─────────██░░██████████─██████████░░██─│
# │─────────██░░██─██░░██──██░░██─██░░██──██░░██─██░░██──██░░██─────██░░██─────────██░░██─────────────────██░░██─│
# │─██████████░░██─██░░██████░░██─██░░██████░░██─██░░██──██░░██████─██░░██████████─██░░██████████─██████████░░██─│
# │─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░██──██░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─│
# │─██████████████─██████████████─██████████████─██████──██████████─██████████████─██████████████─██████████████─│
# ╰──────────────────────────────────────────────────────────────────────────────────────────────────────────────╯

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, src/obj/%.o, $(SRC))

SRC_FOLDER = src
OBJ_FOLDER = src/obj
HEADER_FOLDER = inc

ADD_FLAGS = -lm -lreadline -lncurses

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	        Libft                      	         │
# ╰──────────────────────────────────────────────────────────────────────╯

libft:
	@make -sC lib all;

libclean:
	@make -sC lib clean

relib:
	@make -sC lib re

libtest:
	@make -sC lib test_color

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       PROJECT                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

$(NAME): libft $(OBJ) main.c
	@clear
	@if ! $(CC) $(FLAGS) $(OBJ) main.c lib/libft.a $(ADD_FLAGS) -o $(NAME); then \
		$(call print_cat, "", $(RED), $(GOLD), $(RED_L), $(call pad_word, 10, "ERROR"), $(call pad_word, 12, "COMPILING..")); \
		exit 1; \
	fi
	$(call print_cat, $(CLEAR), $(GOLD), $(GREEN1), $(GREEN1), $(call pad_word, 10, $(NAME)), $(call pad_word, 12, "Compiled~"));

abc: fclean libft $(OBJ) main.c
	$(CC) $(FLAGS) $(OBJ) main.c lib/libft.a $(ADD_FLAGS) -o $(NAME)

src/obj/%.o: src/%.c inc/$(NAME).h
	@if [ ! -e $(OBJ_FOLDER) ]; then\
		mkdir -p $(OBJ_FOLDER);\
	fi
	@if ! $(CC) -c $(FLAGS) $< -o $@; then \
		$(call shmol_cat_error, $(RED), $(RED_L)); \
		exit 1; \
	fi

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       BONUS	                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

FLAGS_MLX = -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lz
SRC_B = $(wildcard srcb/*.c)
OBJ_B = $(patsubst srcb/%.c, srcb/obj/%.o, $(SRC_B))

OBJ_FOLDER_B = srcb/obj

$(NAME_BONUS): bonus

bonus: $(OBJ_B) main_bonus.c inc/$(NAME).h
	@clear
	@if ! $(CC) $(FLAGS) $(OBJ_B) main_bonus.c lib/libft.a $(ADD_FLAGS) -o $(NAME_BONUS); then \
		$(call print_cat, "", $(RED), $(GOLD), $(RED_L), $(call pad_word, 10, "ERROR"), $(call pad_word, 12, "COMPILING..")); \
		exit 1; \
	fi
	$(call print_cat, $(CLEAR), $(GOLD), $(GREEN1), $(C_4R_1G_5B), $(call pad_word, 10, $(NAME_BONUS)), $(call pad_word, 12, "Compiled~"));

srcb/obj/%.o: srcb/%.c inc/$(NAME).h
	@clear
	@if [ ! -e $(OBJ_FOLDER_B) ]; then\
		mkdir -p $(OBJ_FOLDER_B);\
	fi
	@if ! $(CC) -c $(FLAGS) -c $< -o $@; then \
		$(call shmol_cat_error, $(RED), $(RED_L)); \
		exit 1; \
	fi


# ╭────────────────────────────────────────────────────────────────────────────╮
# │─██████████████─██████████████─██████████████─██████─────────██████████████─│
# │─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░██─────────██░░░░░░░░░░██─│
# │─██████░░██████─██░░██████░░██─██░░██████░░██─██░░██─────────██░░██████████─│
# │─────██░░██─────██░░██──██░░██─██░░██──██░░██─██░░██─────────██░░██─────────│
# │─────██░░██─────██░░██──██░░██─██░░██──██░░██─██░░██─────────██░░██████████─│
# │─────██░░██─────██░░██──██░░██─██░░██──██░░██─██░░██─────────██░░░░░░░░░░██─│
# │─────██░░██─────██░░██──██░░██─██░░██──██░░██─██░░██─────────██████████░░██─│
# │─────██░░██─────██░░██──██░░██─██░░██──██░░██─██░░██─────────────────██░░██─│
# │─────██░░██─────██░░██████░░██─██░░██████░░██─██░░██████████─██████████░░██─│
# │─────██░░██─────██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─│
# │─────██████─────██████████████─██████████████─██████████████─██████████████─│
# ╰────────────────────────────────────────────────────────────────────────────╯

# --------------------------------------------------------------------------------- >
# VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --trace-children=yes --track-fds=yes $(V_FLAG)
VALGRIND_OTHER = valgrind --vgdb=yes
V_FLAG = --suppressions="data/ignore_valgrind"
HELLGRIND = valgrind --tool=helgrind ?-g3?

# ↑さ↓ぎょう  を  ↓ほ↑ぞん
git: fclean
	@$(call random_shmol_cat_blink, 作業を保存してるかな.., いいね、いいねえー , $(CLS), );
	@current_date=$$(date); \
	git add .; \
	git commit -m "$$current_date"; \
	git push

NORM_FILE = src/ main.c main_bonus.c inc/

norm: fclean
	@$(call random_shmol_cat_blink, 掃除してるかな..、いいね、いいねえー, giv file to norm, $(CLS), );
	-@read -p 'file...:' path; \
	if [ -z "$$path" ]; then \
		watch -n 0.2 norminette $(NORM_FILE); \
	else \
		watch -n 0.2 norminette $$path; \
	fi

# --------------------------------------------------------------------------------- >
# 																				TEST
test:	libft
	@rm -f ./lib/a.out
	@clear
	-@cc ./lib/test.c ./lib/libft.a -o ./lib/a.out $(ADD_FLAGS)
	@if [ ! -e ./lib/a.out ]; then\
		$(call print_cat, "", $(RED), $(GOLD), $(RED_L), $(call pad_word, 10, "The⠀Cake"), $(call pad_word, 12, "Is⠀A⠀Lie..")); \
		exit 3; \
	fi
	@$(call random_cat, $(call pad_word, 12, "Making"), $(call pad_word, 14, "Science"), $(CLS), $(RESET));
	@lib/a.out

vtest:	libft
	@rm -f ./lib/a.out
	@clear
	-@cc ./lib/test.c ./lib/libft.a -o ./lib/a.out $(ADD_FLAGS)
	@if [ ! -e ./lib/a.out ]; then\
		$(call print_cat, "", $(RED), $(GOLD), $(RED_L), $(call pad_word, 10, "The⠀Cake"), $(call pad_word, 12, "Is⠀A⠀Lie..")); \
		exit 3; \
	fi
	@$(call random_cat, $(call pad_word, 12, "Making"), $(call pad_word, 14, "Science"), $(CLS), $(RESET));
	-@$(VALGRIND) lib/a.out

FLAGS_TEST = -g -fPIE -I$(HEADER_FOLDER)

t2:	libft $(OBJ) inc/$(NAME).h
	@rm -f ./lib/a.out
	@clear
	@$(CC) $(FLAGS_TEST) $(OBJ) ./lib/test.c lib/libft.a $(ADD_FLAGS) -o ./lib/a.out
	@$(call random_cat, $(call pad_word, 12, "TESTING"), $(call pad_word, 14, "SCIENCE"), $(CLS), $(RESET));
	@ lib/a.out

vt2:	libft $(OBJ) inc/$(NAME).h
	@rm -f ./lib/a.out
	@clear
	@$(CC) $(FLAGS_TEST) $(OBJ) ./lib/test.c lib/libft.a $(ADD_FLAGS) -o ./lib/a.out
	@$(call print_cat, "", $(RED), $(GOLD), $(BLUE1), $(call pad_word, 10, "TESTING"), $(call pad_word, 12, "SCIENCE.."));
	-@$(VALGRIND) lib/a.out

# --------------------------------------------------------------------------------- >
# 																				CLEAN
clean: small_clean
	@rm -rf $(OBJ_FOLDER) ./out
	@$(call print_cat, $(CLEAR), $(C_2R_2G_5B), $(C_3R_2G_0B), $(C_4R_5G_0B), $(call pad_word, 10, "Objects"), $(call pad_word, 12, "Exterminated"));

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@make -sC lib clean_silent;
	@$(call print_cat, $(CLEAR), $(C_1R_2G_0B), $(C_3R_0G_0B), $(C_2R_1G_0B), $(call pad_word, 10, "All⠀clean"), $(call pad_word, 12, "Miaster"));

re: fclean all


# <?> .PHONY: test - This declares that test is a phony target,
# 	meaning it's not associated with a file. </?>
.PHONY: all clean fclean small_clean re bonus

.SILENT: $(NAME) bonus

# 	monitor stack activiity
# valgrind --tool=massif --stacks=yes ./your_program
# lldb: clean all
# 	@lldb ./$(NAME) $(ARGS)


# ╭────────────────────────────────────────────────────────────────────────────────────╮
# │─██████████████─████████████████───██████████─██████──────────██████─██████████████─│
# │─██░░░░░░░░░░██─██░░░░░░░░░░░░██───██░░░░░░██─██░░██████████──██░░██─██░░░░░░░░░░██─│
# │─██░░██████░░██─██░░████████░░██───████░░████─██░░░░░░░░░░██──██░░██─██████░░██████─│
# │─██░░██──██░░██─██░░██────██░░██─────██░░██───██░░██████░░██──██░░██─────██░░██─────│
# │─██░░██████░░██─██░░████████░░██─────██░░██───██░░██──██░░██──██░░██─────██░░██─────│
# │─██░░░░░░░░░░██─██░░░░░░░░░░░░██─────██░░██───██░░██──██░░██──██░░██─────██░░██─────│
# │─██░░██████████─██░░██████░░████─────██░░██───██░░██──██░░██──██░░██─────██░░██─────│
# │─██░░██─────────██░░██──██░░██───────██░░██───██░░██──██░░██████░░██─────██░░██─────│
# │─██░░██─────────██░░██──██░░██████─████░░████─██░░██──██░░░░░░░░░░██─────██░░██─────│
# │─██░░██─────────██░░██──██░░░░░░██─██░░░░░░██─██░░██──██████████░░██─────██░░██─────│
# │─██████─────────██████──██████████─██████████─██████──────────██████─────██████─────│
# ╰────────────────────────────────────────────────────────────────────────────────────╯

# C_2R_1G_3B
PURPLE = \033[38;5;97m
# C_4R_3G_0B
GOLD = \033[38;5;178m
# C_0R_4G_0B
GREEN1 = \033[38;5;40m
# C_0R_4G_5B
BLUE1 = \033[38;5;45m

# $(C_1R_0G_5B), $(C_5R_1G_0B), $(C_0R_2G_5B)
# $(RED), $(GOLD), $(BLUE1)

test_color666:
	@$(call random_cat, $(call pad_word, 12, The⠀Cake), $(call pad_word, 14, Is⠀A⠀Lie⠀...), $(CLS), $(RESET));
	@$(call random_cat, $(call pad_word, 13, The⠀Cake), $(call pad_word, 15, Is⠀A⠀Lie⠀...), , $(RESET));


# $(call pad_word, 12, The⠀Cake)
pad_word = $(BLINK)$(shell printf "%$(1)s" "$(2)")$(RESET)
# improve with: STRING1=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1));

# --------------------------------------------------------------------------------- >
# @$(call print_cat, $(CLEAR), $(body), $(eye), $(txt), $(call pad_word, 12, "The⠀Cake"), $(call pad_word, 12, "Is⠀A⠀Lie..."));
# print_cat (resest?)(color_cat)(color_eyes)(color_text)($(padded_txt_top))($(padded_txt_bot))
define print_cat
    echo "$(1)$(2)\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠒⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⠘⡄⠀⠀⠀⠀⠀⠀⣀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀⠀⠀⠁⠉⠉⠉⠒⠊⠉⠀⡇⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜$(3)$(BLINK)⣀⡀$(RESET)$(2)⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠲⢴⠁$(3)$(BLINK)⠛⠁$(RESET)$(2)$(3)$(BLINK)⢀⣄$(RESET)$(2)⠀⠀⠀⢸⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠑⠺⡀⠀⠀⢶⠤$(3)$(BLINK)⠈⠋$(RESET)$(2)⠀⠀⠀⡘⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⡀⠀⠀⠀⠠⣉⠑⠂⠀⢠⠃⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠊⠀⠀⠀⠀⠀⠀⠁⠀⠀⠈⢆⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡆⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠤⠒⠒⠃⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀\n\
	\t\t\t\t\t\t\t	⠀⠔⠑⠄⠀⠀⠀⠀⠀⠀⠀⠀⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠸⡀⠀⢣⠀⠀⠀⠀⠀⠀⠀⠀⡇$(4)$(5)$(2)⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠀⠱⡀⠀⠳⡀⠀⠀⠀⠀⠀⠀⢃$(4)$(6)$(2)⠀⠀⡸⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠑⢄⠀⠈⠒⢄⡀⠀⠀⠀⠸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠑⠦⣀⠀⠈⠉⠐⠒⠒⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⢢⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠉⠐⠒⠠⠤⠤⠤⠤⠔⠂⠠⠤⠤⠤⠄⠐⠒⠂⠉⠉⠉⠉⠉⠁\n$(RESET)"
endef

# --------------------------------------------------------------------------------- >
# @$(call random_cat, $(call pad_word, 12, txt1), $(call pad_word, 12, txt2), $(CLS), $(RESET));
# print_cat (resest?)(color_cat)(color_eyes)(color_text)($(padded_txt_top))($(padded_txt_bot))
define random_cat
	COLOR=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR2=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR3=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
    echo "$(3)$${COLOR}\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠒⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⠘⡄⠀⠀⠀⠀⠀⠀⣀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀⠀⠀⠁⠉⠉⠉⠒⠊⠉⠀⡇⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀$${COLOR2}$(BLINK)⣀⡀$(RESET)$${COLOR}⠀⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠲⢴⠁⠀$${COLOR2}$(BLINK)⠛⠁$(RESET)$${COLOR}$${COLOR2}$(BLINK)⠀⠀⢀⣄$(RESET)$${COLOR}⠀⠀⠀⠀⢸⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠑⠺⡀⠀⠀⢶⠤$${COLOR2}$(BLINK)⠀⠈⠋$(RESET)$${COLOR}⠀⠀⠀⠀⡘⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⡀⠀⠀⠀⠠⣉⠑⠂⠀⢠⠃⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠊⠀⠀⠀⠀⠀⠀⠁⠀⠀⠈⢆⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡆⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠤⠒⠒⠃⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀\n\
	\t\t\t\t\t\t\t	⠀⠔⠑⠄⠀⠀⠀⠀⠀⠀⠀⠀⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠸⡀⠀⢣⠀⠀⠀⠀⠀⠀⠀⠀⡇$${COLOR3}$(1)$${COLOR}⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠀⠱⡀⠀⠳⡀⠀⠀⠀⠀⠀⠀⢃$${COLOR3}$(2)$${COLOR}⠀⠀⡸⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠑⢄⠀⠈⠒⢄⡀⠀⠀⠀⠸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠑⠦⣀⠀⠈⠉⠐⠒⠒⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⢢⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠉⠐⠒⠠⠤⠤⠤⠤⠔⠂⠠⠤⠤⠤⠄⠐⠒⠂⠉⠉⠉⠉⠉⠁\n$(4)"
endef

# --------------------------------------------------------------------------------- >
# @$(call shmol_cat_color, $(color_cat), $(color_txt), text1, txt2, $(CLS), $(RESET));
define shmol_cat_color
	echo "$(5)$(2)\
	\tにゃ~$(1)\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$(2)~ $(3) ~$(1)\n\
	\t\t⠀|、˜\\\\\t\t$(2)$(4)$(1)\n\
	\t\t⠀じしˍ)ノ\n$(6)"
endef
# --------------------------------------------------------------------------------- >
# @$(call random_shmol_cat, text 1, text 2, $(CLS), $(RESET));
# $(1)= $(CLEAR); $(2)= text1; $(3)= text2; $(4)= $(RESET)
define random_shmol_cat
	COLOR=$$(printf "\033[38;5;%dm" $$(shuf -i 1-255 -n 1)); \
	COLOR2=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	echo "$(3)$${COLOR2}\
	\tにゃ~$${COLOR}\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$${COLOR2}~ $(1) ~$${COLOR}\n\
	\t\t⠀|、˜\\\\\t\t$${COLOR2}~ $(2)$${COLOR}\n\
	\t\t⠀じしˍ)ノ\n$(4)"
endef

# // <!> - - - - - - - - - - - </!>
# --------------------------------------------------------------------------------- >
rscs:
	@$(call random_shmol_cat_surligne, text 1, text 2, $(CLS), $(RESET));

define random_shmol_cat_surligne
	COLOR=$$(printf "\033[0m\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR2=$$(printf "\033[48;5;%dm" $$(shuf -i 0-255 -n 1)); \
	echo "$(3)$${COLOR2}\
	\tにゃ~$${COLOR}\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$${COLOR2}~ $(1) ~$${COLOR}\n\
	\t\t⠀|、˜\\\\\t\t$${COLOR2}~ $(2)$${COLOR}\n\
	\t\t⠀じしˍ)ノ\n$(4)"
endef

rscb:
	@$(call random_shmol_cat_blink, text 1, text 2, $(CLS), $(RESET));

define random_shmol_cat_blink
	COLOR=$$(printf "\033[0m\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR2=$$(printf "\e[5m\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	echo "$(3)\n$${COLOR2}\
	\tにゃ~$${COLOR}\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$${COLOR2}~ $(1) ~$${COLOR}\n\
	\t\t⠀|、˜\\\\\t\t$${COLOR2}~ $(2)$${COLOR}\n\
	\t\t⠀じしˍ)ノ\n$(4)"
endef
# // <!> - - - - - - - - - - - </!>
# --------------------------------------------------------------------------------- >
# @$(call shmol_cat_error, $(RED), $(RED_L));
# $(1) = $(color_cat), $(2) = $(color_text)	NO CLS
define shmol_cat_error
	echo "$(2)\
	\tにゃ~$(1)\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$(2)~ somshin wen wong ~$(1)\n\
	\t\t⠀|、˜\\\\\n\
	\t\t⠀じしˍ)ノ\n$(RESET)"
endef

# 					Define all 256 colors
CLEAR = \033[2J\033[H
CLS = \033[2J\033[H
RESET = \033[0m
BLINK = \033[5m
# U+2800 to U+28FF Braile
# <Esc>[38;5;ColorNumberm
BLACK = \033[38;5;0m
RED = \033[38;5;1m
GREEN = \033[38;5;2m
YELLOW = \033[38;5;3m
BLUE = \033[38;5;4m
MAGENTA = \033[38;5;5m
CYAN = \033[38;5;6m
GRAY = \033[38;5;7m

BLACK_L = \033[38;5;8m
RED_L = \033[38;5;9m
GREEN_L = \033[38;5;10m
YELLOW_L = \033[38;5;11m
BLUE_L = \033[38;5;12m
MAGENTA_L = \033[38;5;13m
CYAN_L = \033[38;5;14m
WHITE = \033[38;5;15m

C_0R_0G_0B = \033[38;5;16m
C_0R_0G_1B = \033[38;5;17m
C_0R_0G_2B = \033[38;5;18m
C_0R_0G_3B = \033[38;5;19m
C_0R_0G_4B = \033[38;5;20m
C_0R_0G_5B = \033[38;5;21m
C_0R_1G_0B = \033[38;5;22m
C_0R_1G_1B = \033[38;5;23m
C_0R_1G_2B = \033[38;5;24m
C_0R_1G_3B = \033[38;5;25m
C_0R_1G_4B = \033[38;5;26m
C_0R_1G_5B = \033[38;5;27m
C_0R_2G_0B = \033[38;5;28m
C_0R_2G_1B = \033[38;5;29m
C_0R_2G_2B = \033[38;5;30m
C_0R_2G_3B = \033[38;5;31m
C_0R_2G_4B = \033[38;5;32m
C_0R_2G_5B = \033[38;5;33m
C_0R_3G_0B = \033[38;5;34m
C_0R_3G_1B = \033[38;5;35m
C_0R_3G_2B = \033[38;5;36m
C_0R_3G_3B = \033[38;5;37m
C_0R_3G_4B = \033[38;5;38m
C_0R_3G_5B = \033[38;5;39m
C_0R_4G_0B = \033[38;5;40m
C_0R_4G_1B = \033[38;5;41m
C_0R_4G_2B = \033[38;5;42m
C_0R_4G_3B = \033[38;5;43m
C_0R_4G_4B = \033[38;5;44m
C_0R_4G_5B = \033[38;5;45m
C_0R_5G_0B = \033[38;5;46m
C_0R_5G_1B = \033[38;5;47m
C_0R_5G_2B = \033[38;5;48m
C_0R_5G_3B = \033[38;5;49m
C_0R_5G_4B = \033[38;5;50m
C_0R_5G_5B = \033[38;5;51m
C_1R_0G_0B = \033[38;5;52m
C_1R_0G_1B = \033[38;5;53m
C_1R_0G_2B = \033[38;5;54m
C_1R_0G_3B = \033[38;5;55m
C_1R_0G_4B = \033[38;5;56m
C_1R_0G_5B = \033[38;5;57m
C_1R_1G_0B = \033[38;5;58m
C_1R_1G_1B = \033[38;5;59m
C_1R_1G_2B = \033[38;5;60m
C_1R_1G_3B = \033[38;5;61m
C_1R_1G_4B = \033[38;5;62m
C_1R_1G_5B = \033[38;5;63m
C_1R_2G_0B = \033[38;5;64m
C_1R_2G_1B = \033[38;5;65m
C_1R_2G_2B = \033[38;5;66m
C_1R_2G_3B = \033[38;5;67m
C_1R_2G_4B = \033[38;5;68m
C_1R_2G_5B = \033[38;5;69m
C_1R_3G_0B = \033[38;5;70m
C_1R_3G_1B = \033[38;5;71m
C_1R_3G_2B = \033[38;5;72m
C_1R_3G_3B = \033[38;5;73m
C_1R_3G_4B = \033[38;5;74m
C_1R_3G_5B = \033[38;5;75m
C_1R_4G_0B = \033[38;5;76m
C_1R_4G_1B = \033[38;5;77m
C_1R_4G_2B = \033[38;5;78m
C_1R_4G_3B = \033[38;5;79m
C_1R_4G_4B = \033[38;5;80m
C_1R_4G_5B = \033[38;5;81m
C_1R_5G_0B = \033[38;5;82m
C_1R_5G_1B = \033[38;5;83m
C_1R_5G_2B = \033[38;5;84m
C_1R_5G_3B = \033[38;5;85m
C_1R_5G_4B = \033[38;5;86m
C_1R_5G_5B = \033[38;5;87m
C_2R_0G_0B = \033[38;5;88m
C_2R_0G_1B = \033[38;5;89m
C_2R_0G_2B = \033[38;5;90m
C_2R_0G_3B = \033[38;5;91m
C_2R_0G_4B = \033[38;5;92m
C_2R_0G_5B = \033[38;5;93m
C_2R_1G_0B = \033[38;5;94m
C_2R_1G_1B = \033[38;5;95m
C_2R_1G_2B = \033[38;5;96m
C_2R_1G_3B = \033[38;5;97m
C_2R_1G_4B = \033[38;5;98m
C_2R_1G_5B = \033[38;5;99m
C_2R_2G_0B = \033[38;5;100m
C_2R_2G_1B = \033[38;5;101m
C_2R_2G_2B = \033[38;5;102m
C_2R_2G_3B = \033[38;5;103m
C_2R_2G_4B = \033[38;5;104m
C_2R_2G_5B = \033[38;5;105m
C_2R_3G_0B = \033[38;5;106m
C_2R_3G_1B = \033[38;5;107m
C_2R_3G_2B = \033[38;5;108m
C_2R_3G_3B = \033[38;5;109m
C_2R_3G_4B = \033[38;5;110m
C_2R_3G_5B = \033[38;5;111m
C_2R_4G_0B = \033[38;5;112m
C_2R_4G_1B = \033[38;5;113m
C_2R_4G_2B = \033[38;5;114m
C_2R_4G_3B = \033[38;5;115m
C_2R_4G_4B = \033[38;5;116m
C_2R_4G_5B = \033[38;5;117m
C_2R_5G_0B = \033[38;5;118m
C_2R_5G_1B = \033[38;5;119m
C_2R_5G_2B = \033[38;5;120m
C_2R_5G_3B = \033[38;5;121m
C_2R_5G_4B = \033[38;5;122m
C_2R_5G_5B = \033[38;5;123m
C_3R_0G_0B = \033[38;5;124m
C_3R_0G_1B = \033[38;5;125m
C_3R_0G_2B = \033[38;5;126m
C_3R_0G_3B = \033[38;5;127m
C_3R_0G_4B = \033[38;5;128m
C_3R_0G_5B = \033[38;5;129m
C_3R_1G_0B = \033[38;5;130m
C_3R_1G_1B = \033[38;5;131m
C_3R_1G_2B = \033[38;5;132m
C_3R_1G_3B = \033[38;5;133m
C_3R_1G_4B = \033[38;5;134m
C_3R_1G_5B = \033[38;5;135m
C_3R_2G_0B = \033[38;5;136m
C_3R_2G_1B = \033[38;5;137m
C_3R_2G_2B = \033[38;5;138m
C_3R_2G_3B = \033[38;5;139m
C_3R_2G_4B = \033[38;5;140m
C_3R_2G_5B = \033[38;5;141m
C_3R_3G_0B = \033[38;5;142m
C_3R_3G_1B = \033[38;5;143m
C_3R_3G_2B = \033[38;5;144m
C_3R_3G_3B = \033[38;5;145m
C_3R_3G_4B = \033[38;5;146m
C_3R_3G_5B = \033[38;5;147m
C_3R_4G_0B = \033[38;5;148m
C_3R_4G_1B = \033[38;5;149m
C_3R_4G_2B = \033[38;5;150m
C_3R_4G_3B = \033[38;5;151m
C_3R_4G_4B = \033[38;5;152m
C_3R_4G_5B = \033[38;5;153m
C_3R_5G_0B = \033[38;5;154m
C_3R_5G_1B = \033[38;5;155m
C_3R_5G_2B = \033[38;5;156m
C_3R_5G_3B = \033[38;5;157m
C_3R_5G_4B = \033[38;5;158m
C_3R_5G_5B = \033[38;5;159m
C_4R_0G_0B = \033[38;5;160m
C_4R_0G_1B = \033[38;5;161m
C_4R_0G_2B = \033[38;5;162m
C_4R_0G_3B = \033[38;5;163m
C_4R_0G_4B = \033[38;5;164m
C_4R_0G_5B = \033[38;5;165m
C_4R_1G_0B = \033[38;5;166m
C_4R_1G_1B = \033[38;5;167m
C_4R_1G_2B = \033[38;5;168m
C_4R_1G_3B = \033[38;5;169m
C_4R_1G_4B = \033[38;5;170m
C_4R_1G_5B = \033[38;5;171m
C_4R_2G_0B = \033[38;5;172m
C_4R_2G_1B = \033[38;5;173m
C_4R_2G_2B = \033[38;5;174m
C_4R_2G_3B = \033[38;5;175m
C_4R_2G_4B = \033[38;5;176m
C_4R_2G_5B = \033[38;5;177m
C_4R_3G_0B = \033[38;5;178m
C_4R_3G_1B = \033[38;5;179m
C_4R_3G_2B = \033[38;5;180m
C_4R_3G_3B = \033[38;5;181m
C_4R_3G_4B = \033[38;5;182m
C_4R_3G_5B = \033[38;5;183m
C_4R_4G_0B = \033[38;5;184m
C_4R_4G_1B = \033[38;5;185m
C_4R_4G_2B = \033[38;5;186m
C_4R_4G_3B = \033[38;5;187m
C_4R_4G_4B = \033[38;5;188m
C_4R_4G_5B = \033[38;5;189m
C_4R_5G_0B = \033[38;5;190m
C_4R_5G_1B = \033[38;5;191m
C_4R_5G_2B = \033[38;5;192m
C_4R_5G_3B = \033[38;5;193m
C_4R_5G_4B = \033[38;5;194m
C_4R_5G_5B = \033[38;5;195m
C_5R_0G_0B = \033[38;5;196m
C_5R_0G_1B = \033[38;5;197m
C_5R_0G_2B = \033[38;5;198m
C_5R_0G_3B = \033[38;5;199m
C_5R_0G_4B = \033[38;5;200m
C_5R_0G_5B = \033[38;5;201m
C_5R_1G_0B = \033[38;5;202m
C_5R_1G_1B = \033[38;5;203m
C_5R_1G_2B = \033[38;5;204m
C_5R_1G_3B = \033[38;5;205m
C_5R_1G_4B = \033[38;5;206m
C_5R_1G_5B = \033[38;5;207m
C_5R_2G_0B = \033[38;5;208m
C_5R_2G_1B = \033[38;5;209m
C_5R_2G_2B = \033[38;5;210m
C_5R_2G_3B = \033[38;5;211m
C_5R_2G_4B = \033[38;5;212m
C_5R_2G_5B = \033[38;5;213m
C_5R_3G_0B = \033[38;5;214m
C_5R_3G_1B = \033[38;5;215m
C_5R_3G_2B = \033[38;5;216m
C_5R_3G_3B = \033[38;5;217m
C_5R_3G_4B = \033[38;5;218m
C_5R_3G_5B = \033[38;5;219m
C_5R_4G_0B = \033[38;5;220m
C_5R_4G_1B = \033[38;5;221m
C_5R_4G_2B = \033[38;5;222m
C_5R_4G_3B = \033[38;5;223m
C_5R_4G_4B = \033[38;5;224m
C_5R_4G_5B = \033[38;5;225m
C_5R_5G_0B = \033[38;5;226m
C_5R_5G_1B = \033[38;5;227m
C_5R_5G_2B = \033[38;5;228m
C_5R_5G_3B = \033[38;5;229m
C_5R_5G_4B = \033[38;5;230m
C_5R_5G_5B = \033[38;5;231m
