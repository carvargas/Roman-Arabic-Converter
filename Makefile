p3server: server.o convertToRoman.o convertToArabic.o otherFuncs.o
	gcc server.o convertToRoman.o convertToArabic.o otherFuncs.o -o p3server -lsocket -lnsl
p3client: client.o
	gcc client.o -o p3client -lsocket -lnsl
server.o: server.c
	gcc -c server.c
convertToRoman.o: convertToRoman.c
	gcc -c convertToRoman.c
convertToArabic.o: convertToArabic.c
	gcc -c convertToArabic.c
otherFuncs.o: otherFuncs.c
	gcc -c otherFuncs.c
client.o: client.c
	gcc -c client.c
clean:
	-rm -f *.o core p3server p3client