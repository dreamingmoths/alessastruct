SOURCE_FILES  = $(shell find src -name *.c)
OBJECT_FILES  = $(patsubst %.c, build/%.o, $(SOURCE_FILES))
TARGET 		 := build/alessastruct

all: $(TARGET)

build:
	$(MAKE) clean
	mkdir -p build/src/alessastruct
	$(MAKE) $(TARGET)

clean:
	rm -rf build

build/%.o: %.c
	gcc -o $@ -Iinclude -c $^

$(TARGET): $(OBJECT_FILES)
	gcc -o $@ $^

.PHONY: all build clean
