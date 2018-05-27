all: shellload32 shellload64

shellload32: main.c Makefile
	gcc -m32 -O99 -static -fno-stack-protector -z execstack -o $@ main.c
	strip $@
	@#upx --ultra-brute $@
	ls -lh $@

shellload64: main.c Makefile
	gcc -m64 -O99 -static -fno-stack-protector -z execstack -o $@ main.c
	strip $@
	@#upx --ultra-brute $@
	ls -lh $@

.PHONY: clean
clean:
	-rm *.o
	-rm shelload

.PHONY: test
test: all
	@-rm itworks
	./shellload64 "6a3b589948bb2f62696e2f736800534889e7682d6300004889e652e80e000000746f756368206974776f726b730056574889e60f05"
	sleep 1
	rm itworks

.PHONY: watch
watch:
	find *.c Makefile | entr make test
