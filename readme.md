COMANDO PARA COMPILAR EL PROGRAMA (Con todos los archivos .c necesarios):
gcc main/main.c lib/sqlite3/sqlite3.c db/dbConnection.c db/getData.c db/postData.c main/login/loginProfesional.c main/menuProfesional/menuProfesional.c utils/fechas.c utils/prestamo/prestamo.c

COMANDO PARA PROBAR INVERSIONES:
g++ containers/containers.cpp main/inversiones/inversiones.cpp main/inversiones/stockAPI.cpp ../C/db/dbConnection.c utils/db/getDataCPP.cpp -o inversiones-test -lcurl -lsqlite3
