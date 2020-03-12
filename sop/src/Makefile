#
# A simple makefile for managing build of project composed of Cpp source files.
#


# It is likely that default Cpp compiler is already g++, but explicitly
# set, just to be sure
CC = g++

# The CFLAGS variable sets compile flags for gcc:
#  -g          compile with debug informationre
#  -Wall       give verbose compiler warnings
#  -O0         do not optimize generated code
#  -std=c++11  use the C++11 standard language definition
CFLAGS = -g -Wall -O0 -std=c++11 -pthread

# In this section, you list the files that are part of the project.
# If you add/change names of source files, here is where you
# edit the Makefile.
SOURCES = Main.cpp Candidato.cpp Contador.cpp Validator.cpp utils.cpp Queue.cpp ResultadoVotos.cpp
OBJECTS = $(SOURCES:.cpp=.cpp)
TARGET = demo


# The first target defined in the makefile is the one
# used when make is invoked with no argument. Given the definitions
# above, this Makefile file will build the one named TARGET and
# assume that it depends on all the named OBJECTS files.

$(TARGET) : $(OBJECTS)
	reset && $(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" is used to remove all compiled object files.

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
