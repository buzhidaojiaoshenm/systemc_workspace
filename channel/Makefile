TARGET ?= sc_main
SDIR ?= .
ODIR ?= .

SRC = $(wildcard $(SDIR)/$(TARGET).cpp)
OBJ = $(SRC:$(SDIR)/%.c=$(ODIR)/%.o)

CXX = g++
CXXFLAGS = -I$(IDIR)
CXXFLAGS += -g -O0
CFLAGS += -Wall
SCPATH = /home/sjh/work/systemc-3.0.0
LIBS = -lm

.PHONY:all
all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -I$(SCPATH)/include -L. -L$(SCPATH)/lib-linux64 -Wl,-rpath $(SCPATH)/lib-linux64 $^ $(LIBS) -o $@ -lsystemc
	@echo "successfull make"

$(ODIR)/%.o: $(SDIR)/%.c
	$(CXX) -C $(CXXFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET)