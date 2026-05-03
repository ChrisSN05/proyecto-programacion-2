cmake_minimum_required(VERSION 4.1)
project(proyecto_programacion_2)

set(CMAKE_CXX_STANDARD 26)

add_executable(proyecto_programacion_2

        includes/Equipo.h
        includes/EquipoComputo.h
        includes/EquipoLaboratorio.h
        includes/EquipoMedico.h
        includes/Incidencia.h
        includes/OrdenadorEquipos.h
        includes/Simulador.h
        includes/ArchivoInvalidoException.h
        includes/FormatoInvalidoException.h
        includes/OperacionInconsistenteException.h
        includes/CalculadorPrioridad.h
        includes/BuscadorEquipos.h
        includes/GeneradorDatosPrueba.h
        includes/CargarDatos.h
        includes/GeneradorReporte.h
        includes/SistemaMantenimiento.h
        includes/Menu.h


        src/Equipo.cpp
        src/EquipoComputo.cpp
        src/EquipoLaboratorio.cpp
        src/EquipoMedico.cpp
        src/CalculadorPrioridad.cpp
        src/OrdenadorEquipos.cpp
        src/BuscadorEquipos.cpp
        src/GeneradorDatosPrueba.cpp
        src/CargarDatos.cpp
        src/GeneradorReporte.cpp
        src/Simulador.cpp
        src/SistemaMantenimiento.cpp
        src/Menu.cpp
        src/Incidencia.cpp

        
        main.cpp

)

target_include_directories(proyecto_programacion_2 PRIVATE includes)

target_compile_definitions(proyecto_programacion_2 PRIVATE
        PROJECT_ROOT="${CMAKE_CURRENT_SOURCE_DIR}"
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Archivos)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Reportes)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Documentacion)
