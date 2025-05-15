CXX = g++
CC = gcc

LIB_DIR = ../..
# =====================================================================================================================




# ==== kato source file ===============================================================================================
KATO_DIR = $(LIB_DIR)

KATO_SOURCES = $(KATO_DIR)/src/function.cpp
KATO_HEADERS = $(KATO_DIR)/include/kato/function.h $(KATO_DIR)/include/kato/log.h
KATO_OBJS = $(addprefix .kato_, $(addsuffix .o, $(basename $(notdir $(KATO_SOURCES)))))

KATO_CXXFLAGS = -I$(KATO_DIR)/include
# ==== kato source file ===============================================================================================




# ==== test source files ==============================================================================================
TEST_EXE = test_function
TEST_SOURCES = main.cpp
TEST_OBJS = $(addprefix ., $(addsuffix .o, $(basename $(notdir $(TEST_SOURCES)))))
# ==== test source files ==============================================================================================




# ==== gcc flags ======================================================================================================
CXXFLAGS = -Wall -Wextra -Wunused -Wformat -O3
CXXFLAGS += $(KATO_CXXFLAGS)

LIBS = -lpthread

CFLAGS = $(CXXFLAGS)
CFLAGS_STD = $(CFLAGS) -std=c17
CXXFLAGS_STD = $(CXXFLAGS) -std=c++17
# ==== gcc flags ======================================================================================================




# ==== build rules ====================================================================================================
.kato_%.o: $(KATO_DIR)/src/%.cpp $(KATO_HEADERS)
	$(CXX) $(CXXFLAGS_STD) -c -o $@ $<

.%.o: %.cpp
	$(CXX) $(CXXFLAGS_STD) -c -o $@ $<

all: $(TEST_EXE)
	@echo Build complete

$(TEST_EXE): $(TEST_OBJS) $(KATO_OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean_test:
	rm -f $(TEST_EXE) $(TEST_OBJS)

clean_kato:
	rm -f $(TEST_EXE) $(KATO_OBJS)

clean: clean_test clean_kato
# ==== build rules ====================================================================================================
