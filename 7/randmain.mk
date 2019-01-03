randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) randlibhw.c -fPIC -c -o randlibhw.o
	$(CC) $(CFLAGS) randlibhw.o -shared -o randlibhw.so
randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) randlibsw.c -fPIC -c -o randlibsw.o
	$(CC) $(CFLAGS) randlibsw.o -shared -o randlibsw.so
randmain: randmain.o randcpuid.o
	$(CC) $(CFLAGS) randmain.o randcpuid.o -ldl -Wl,-rpath=$PWD -o randmain
