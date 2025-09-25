CC = g++
CFLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef \
   -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations \
   -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ \
   -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion\
   -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2\
   -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers\
   -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo\
   -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits\
   -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE -DCOLOR_PRINT
   
OBJECTS = main.o stack.o
EXECUTABLE_NAME = main.exe
DIR_BUILD = Build
#CFLAGSH = -DCONSOLE

all: $(EXECUTABLE_NAME)

.PHONY = all clean start start_out_to_file

$(EXECUTABLE_NAME): make_folder  $(OBJECTS)
	$(CC) $(addprefix ./$(DIR_BUILD)/, $(OBJECTS)) -o ./$(DIR_BUILD)/$(EXECUTABLE_NAME)


$(OBJECTS): %.o: %.cpp
	$(CC) $(CFLAGS) $(CFLAGSH) -c $^ -o ./$(DIR_BUILD)/$@

make_folder:
	mkdir -p $(DIR_BUILD)/

start:
	./$(DIR_BUILD)/$(EXECUTABLE_NAME)

clean:
	rm -rf ./$(DIR_BUILD)/
	rm -f out.txt