# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 16:41:00 by pacda-si          #+#    #+#              #
#    Updated: 2025/11/25 20:05:11 by pacda-si         ###   ########.fr        #
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
# Build imgui as a static library with OpenGL3 + SDL2 backends
LIB_NAME    = libimgui.a

SRCS        = imgui.cpp \
			  imgui_draw.cpp \
			  imgui_tables.cpp \
			  imgui_widgets.cpp \
			  imgui_demo.cpp \
			  imgui_impl_opengl3.cpp \
			  imgui_impl_sdl2.cpp

OBJS_DIR    = objs
OBJS        = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

# Include directories for imgui headers and dependencies
CXXFLAGS_INCLUDES = -I. \
					-I../glad \
					-I../KHR \
					$(shell pkg-config --cflags sdl2)

# ────────────────────────────── Compiler ────────────────────────────
CXX         = g++
AR          = ar
CXXFLAGS    = -Werror -Wall -Wextra -g3 -fPIC $(CXXFLAGS_INCLUDES)
ARFLAGS     = rcs

# ────────────────────────────── Rules ───────────────────────────────
all: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	@echo "$(BLOOD_RED)$(BOLD)Archiving $(LIB_NAME)...$(RESET)"
	@$(AR) $(ARFLAGS) $(LIB_NAME) $(OBJS)
	@echo "$(NEON_GREEN)$(BOLD)Built $(LIB_NAME) successfully. ✔\n$(RESET)"

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "$(CYAN_SHOCK)Compiling $<...$(RESET)"
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
	@if [ -f "$(LIB_NAME)" ]; then \
		echo "$(SUNBURST_YELLOW)$(BOLD)Removing library..$(RESET)"; \
		rm -f $(LIB_NAME); \
		echo "$(NEON_GREEN)$(BOLD)Done. ✔$(RESET)"; \
	else \
		echo "$(CYAN_SHOCK)$(BOLD)No library to remove. Skipping fclean.$(RESET)"; \
	fi

re: fclean all

default: all

.PHONY: default all re fclean clean