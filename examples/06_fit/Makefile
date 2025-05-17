CXX = g++
CC = gcc

LIB_DIR = ../..
# =====================================================================================================================




# ==== kato source file ===============================================================================================
KATO_DIR = $(LIB_DIR)
KATO_HEADERS =  $(KATO_DIR)/include/kato/math_addons.h $(KATO_DIR)/include/kato/function.h
KATO_CXXFLAGS = -I$(KATO_DIR)/include
KATO_LIBS = `pkg-config --cflags --libs openblas`
# ==== kato source file ===============================================================================================




# ==== test source files ==============================================================================================
TEST_EXE = test_fit
TEST_SOURCES = main.cpp
TEST_OBJS = $(addprefix ., $(addsuffix .o, $(basename $(notdir $(TEST_SOURCES)))))
# ==== test source files ==============================================================================================




# ==== gcc flags ======================================================================================================
CXXFLAGS = -Wall -Wextra -Wunused -Wformat -O3
CXXFLAGS += $(KATO_CXXFLAGS)

LIBS = -lpthread
LIBS += $(KATO_LIBS)

CFLAGS = $(CXXFLAGS)
CFLAGS_STD = $(CFLAGS) -std=c17
CXXFLAGS_STD = $(CXXFLAGS) -std=c++17
# ==== gcc flags ======================================================================================================




# ==== build rules ====================================================================================================
.%.o: %.cpp
	$(CXX) $(CXXFLAGS_STD) -c -o $@ $<

all: $(TEST_EXE)
	@echo Build complete

$(TEST_EXE): $(TEST_OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean_test:
	rm -f $(TEST_EXE) $(TEST_OBJS)

clean: clean_test
# ==== build rules ====================================================================================================
