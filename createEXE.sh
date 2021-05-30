gcc lib/sqlite3/sqlite3.c db/dbConnection.c db/C/getData.c db/C/postData.c main/C/login/loginProfesional.c main/C/menuProfesional/menuProfesional.c main/C/utils/fechas.c main/C/utils/prestamo/prestamo.c -c

g++ main/C++/utils/inversiones/stockAPI.cpp main/C++/utils/inversiones/inversiones.cpp main/main.cpp db/C++/getDataCPP.cpp db/C++/postDataCPP.cpp main/C++/login/loginCliente.cpp main/C++/utils/containers/containers.cpp main/C++/menuCliente/menuCliente.cpp -c

g++ stockAPI.o inversiones.o containers.o dbConnection.o fechas.o getData.o getDataCPP.o postDataCPP.o loginCliente.o loginProfesional.o main.o menuCliente.o menuProfesional.o postData.o prestamo.o sqlite3.o -o app -lcurl -lsqlite3

rm *.o

./app