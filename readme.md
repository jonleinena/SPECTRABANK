COMANDO PARA COMPILAR EL PROGRAMA (Con todos los archivos .c necesarios):
gcc main/main.c lib/sqlite3/sqlite3.c db/dbConnection.c db/C/getData.c db/C/postData.c main/C/login/loginProfesional.c main/C/menuProfesional/menuProfesional.c main/C/utils/fechas.c main/C/utils/prestamo/prestamo.c

COMANDO PARA PROBAR INVERSIONES:
g++ containers/containers.cpp main/inversiones/inversiones.cpp main/inversiones/stockAPI.cpp ../C/db/dbConnection.c utils/db/getDataCPP.cpp -o inversiones-test -lcurl -lsqlite3
