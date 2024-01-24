@echo off
REM Este é um arquivo de lote para compilar e construir o programa
g++ -IC:\SFML-2.5.1\include -c ball.cpp -o main.o
if errorlevel 1 (
    echo Erro durante a compilação. Pressione qualquer tecla para continuar...
    pause
    exit /b 1
)

g++ -LC:\SFML-2.5.1\lib .\main.o -o main.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows
if errorlevel 1 (
    echo Erro durante a construção do executável. Pressione qualquer tecla para continuar...
    pause
    exit /b 1
)
