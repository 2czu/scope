# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 16:41:00 by pacda-si          #+#    #+#              #
#    Updated: 2025/12/12 17:26:26 by pacda-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ────────────────────────────── Colors ──────────────────────────────
BOLD            = \033[1m
RESET           = \033[0m
GREEN           = \033[0;32m
CYAN            = \033[0;36m
LIGHT_RED       = \033[91m
LIGHT_GREEN     = \033[92m
LIGHT_CYAN      = \033[96m
BROWN           = \033[38;5;94m

NEON_GREEN      = \033[38;5;46m
ELECTRIC_BLUE   = \033[38;5;51m
HOT_PINK        = \033[38;5;198m
BLOOD_RED       = \033[38;5;196m
SUNBURST_YELLOW = \033[38;5;226m
DEEP_ORANGE     = \033[38;5;208m
PURPLE_RAVE     = \033[38;5;129m
CYAN_SHOCK      = \033[38;5;51m

BG_FIRE         = \033[48;5;196m
BG_LIME         = \033[48;5;46m
BG_ULTRA_BLUE   = \033[48;5;21m
BG_MAGENTA      = \033[48;5;201m

# ────────────────────────────── Files ───────────────────────────────
NAME        = scope
SRCS_DIR    = ./srcs

SRCS        = $(SRCS_DIR)/main.cpp \
			  $(SRCS_DIR)/glad.c \
			  $(SRCS_DIR)/Shader.cpp \
			  $(SRCS_DIR)/ShaderProgram.cpp \
			  $(SRCS_DIR)/Application.cpp \
			  $(SRCS_DIR)/Camera.cpp \
			  $(SRCS_DIR)/Material.cpp \
			  $(SRCS_DIR)/Mesh.cpp \
			  $(SRCS_DIR)/Object3D.cpp \
			  $(SRCS_DIR)/Parser.cpp \
			  $(SRCS_DIR)/Renderer.cpp \
			  $(SRCS_DIR)/Scene.cpp \
			  $(SRCS_DIR)/Texture.cpp \
			  $(SRCS_DIR)/EventHandler.cpp \
			  $(SRCS_DIR)/LightSource.cpp \
			  $(SRCS_DIR)/Transform.cpp
			  

OBJS_DIR    = objs
OBJS        = $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

HEADERS =	includes/

IMGUI_DIR   = ./third_party/imgui
IMGUI_LIB   = $(IMGUI_DIR)/libimgui.a
IMGUI_FLAGS = -I$(IMGUI_DIR) -I./third_party/glad -I./third_party/KHR

OGL_FLAGS   = -lGL -lGLU -lglut -lSDL2


# ────────────────────────────── Compiler ────────────────────────────
CXX         = g++
CXXFLAGS    = -Werror -Wall -Wextra -g3 -O3

# ────────────────────────────── Rules ───────────────────────────────
all: $(NAME)

$(NAME): $(IMGUI_LIB) $(OBJS) $(HEADERS)
	@echo "$(BLOOD_RED)$(BOLD)Making $(NAME)...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJS) $(IMGUI_LIB) $(IMGUI_FLAGS) -o $(NAME) $(OGL_FLAGS)
	@echo "$(NEON_GREEN)$(BOLD)Made $(NAME) without any problem. ✔\n$(RESET)"

$(IMGUI_LIB):
	@echo "$(CYAN_SHOCK)$(BOLD)Building imgui library...$(RESET)"
	@$(MAKE) -C $(IMGUI_DIR)
	@echo "$(NEON_GREEN)$(BOLD)ImGui library built. ✔$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if [ -d "$(OBJS_DIR)" ]; then \
		echo "$(SUNBURST_YELLOW)$(BOLD)Removing all object files..$(RESET)"; \
		rm -rf $(OBJS_DIR); \
		echo "$(NEON_GREEN)$(BOLD)Done. ✔$(RESET)"; \
	else \
		echo "$(CYAN_SHOCK)$(BOLD)No object files to remove. Skipping clean.$(RESET)"; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(SUNBURST_YELLOW)$(BOLD)Removing executable..$(RESET)"; \
		rm -f $(NAME); \
		echo "$(NEON_GREEN)$(BOLD)Done. ✔$(RESET)"; \
	else \
		echo "$(CYAN_SHOCK)$(BOLD)No executable to remove. Skipping fclean.$(RESET)"; \
	fi
	@$(MAKE) -C $(IMGUI_DIR) fclean

re: fclean all

default: all

.PHONY: default all re fclean clean