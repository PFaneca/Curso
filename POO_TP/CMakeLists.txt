cmake_minimum_required(VERSION 3.24)
project(TP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP main.cpp Aparelho.cpp Processador.cpp Propriedade.cpp Regra.cpp Sensor.cpp Terminal.cpp Zona.cpp Propriedades/Temperatura.cpp Propriedades/Temperatura.h Habitacao.cpp Habitacao.h Regras/Maior.cpp Regras/Maior.h Regras/Entre.cpp Regras/Entre.h Aparelhos/Aquecedor.h Aparelhos/Aquecedor.cpp Aparelho.h Interacao.cpp Interacao.h Propriedades/Luz.h Propriedades/Radiacao.h Propriedades/Vibracao.h Propriedades/Humidade.h Propriedades/Fumo.h Propriedades/Som.h Regras/Igual.cpp Regras/Igual.h Regras/Menor.cpp Regras/Menor.h Regras/Fora.h Regras/Fora.cpp Aparelhos/Aspersor.h Aparelhos/Aspersor.cpp Aparelhos/Refrigerador.cpp Aparelhos/Refrigerador.h Aparelhos/Lampada.h Aparelhos/Lampada.cpp)

target_link_libraries(${PROJECT_NAME} C:/Users/ASUS/POO-2324/PDCurses-3.9/wincon/pdcurses.a)