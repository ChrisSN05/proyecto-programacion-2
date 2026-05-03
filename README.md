# Proyecto Programación II

## Sistema de Planificación Inteligente de Mantenimiento

Este proyecto corresponde al curso de Programación II. El sistema simula la planificación diaria de mantenimiento para equipos de un laboratorio, utilizando programación orientada a objetos en C++.

El programa trabaja con equipos, incidencias, cálculo automático de prioridad, ordenamiento de equipos, búsqueda por código, aplicación de mantenimiento y generación de reportes durante una simulación de 30 días.

---

## Objetivo del sistema

El objetivo principal del sistema es automatizar la selección de equipos que requieren mantenimiento, tomando en cuenta:

- Criticidad del equipo
- Cantidad de incidencias activas
- Tiempo inactivo acumulado
- Estado actual del equipo

Con esta información, el sistema calcula la prioridad de cada equipo y selecciona diariamente los equipos más urgentes para recibir mantenimiento.

---

## Tecnologías utilizadas

- Lenguaje: C++
- Estándar: C++17 o superior
- Sistema de construcción: CMake
- Manejo de archivos de texto
- Programación orientada a objetos
- Herencia
- Polimorfismo
- Excepciones personalizadas
- Algoritmo propio de ordenamiento
- Búsqueda binaria
- Patrón de diseño Template Method

---

## Archivos del sistema

El sistema utiliza archivos de texto para almacenar los datos iniciales y generar los reportes de la simulación.

### Carpeta Archivos

Contiene los datos base del sistema:

- equipos.txt
- incidencias.txt

Si estos archivos no existen, el sistema los genera automáticamente al iniciar.

### Carpeta Reportes

Contiene los reportes generados después de ejecutar la simulación:

- reporte_dia_1.txt
- reporte_dia_2.txt
- ...
- reporte_dia_30.txt
- reporte_final.txt

Los reportes se generan únicamente cuando se ejecuta la simulación de 30 días.

---

## Menú principal

Al ejecutar el programa se muestra el siguiente menú:

1. Regenerar datos de prueba
2. Cargar datos desde archivos
3. Registrar equipo manualmente
4. Registrar incidencia manualmente
5. Ejecutar simulación de 30 días
6. Ver resumen cargado
7. Salir

### Opción 1: Regenerar datos de prueba

Genera nuevamente los archivos de prueba con equipos e incidencias. Esta opción sobrescribe los datos anteriores y carga los nuevos datos en memoria.

### Opción 2: Cargar datos desde archivos

Carga en memoria los equipos e incidencias existentes en la carpeta Archivos.

### Opción 3: Registrar equipo manualmente

Permite registrar un equipo desde consola.

Tipos válidos:

- COMPUTO
- LABORATORIO
- MEDICO

### Opción 4: Registrar incidencia manualmente

Permite registrar una incidencia asociada a un equipo existente.

Severidades válidas:

- ALTA
- MEDIA
- BAJA

### Opción 5: Ejecutar simulación de 30 días

Ejecuta la simulación completa.

Durante cada día el sistema:

1. Degrada el estado de los equipos
2. Activa incidencias según el día correspondiente
3. Calcula la prioridad de cada equipo
4. Ordena los equipos por prioridad
5. Selecciona máximo 3 equipos para mantenimiento
6. Aplica mantenimiento
7. Genera un reporte diario

Al finalizar la simulación se genera también un reporte final.

### Opción 6: Ver resumen cargado

Muestra la cantidad de equipos e incidencias cargadas en memoria.

### Opción 7: Salir

Finaliza la ejecución del sistema.

---

## Flujo recomendado para probar el sistema

Al ejecutar el programa, el sistema carga automáticamente los datos iniciales.

Para probarlo:

1. Ejecutar el programa
2. Seleccionar la opción 6
3. Verificar que existan 100 equipos y 300 incidencias
4. Seleccionar la opción 5
5. Esperar que se simulen los 30 días
6. Revisar la carpeta Reportes
7. Abrir reporte_dia_1.txt y reporte_final.txt

Resultado esperado en la opción 6:

- Equipos cargados: 100
- Incidencias cargadas: 300

Después de ejecutar la simulación deben generarse 31 reportes:

- 30 reportes diarios
- 1 reporte final

---

## Fórmula de prioridad

El sistema calcula la prioridad de cada equipo usando la siguiente fórmula:

prioridad = (criticidad * 0.5) + (incidencias_activas * 0.3) + (tiempo_inactivo * 0.2)

Esta fórmula se implementa en la clase CalculadorPrioridad.

La prioridad se recalcula durante la simulación para decidir qué equipos deben ser atendidos primero.

---

## Clases principales

### Equipo

Clase base abstracta que representa un equipo general.

Contiene atributos comunes como:

- Código
- Nombre
- Criticidad
- Estado
- Tiempo inactivo
- Último día de atención
- Prioridad
- Incidencias asociadas

Define métodos virtuales que son implementados por las clases derivadas.

### EquipoComputo

Representa equipos de cómputo. Implementa su propia forma de degradarse y recibir mantenimiento.

También posee el método específico revisarSoftware().

### EquipoLaboratorio

Representa equipos de laboratorio. Implementa su propia forma de degradarse y recibir mantenimiento.

### EquipoMedico

Representa equipos médicos. Implementa su propia forma de degradarse y recibir mantenimiento.

También posee el método específico calibrarSensores().

### Incidencia

Representa un problema asociado a un equipo.

Cada incidencia contiene:

- Código
- Código del equipo asociado
- Severidad
- Día de registro
- Estado activo o cerrado

### CalculadorPrioridad

Se encarga de calcular la prioridad de un equipo usando la fórmula definida para el sistema.

### OrdenadorEquipos

Contiene el algoritmo propio de ordenamiento. Utiliza Merge Sort para ordenar equipos por prioridad y por código.

### BuscadorEquipos

Realiza búsqueda binaria para localizar equipos por código.

### GeneradorDatosPrueba

Genera datos automáticos para probar el sistema:

- 100 equipos
- 300 incidencias

### CargarDatos

Lee los archivos de texto y carga los datos en memoria.

También valida:

- Formato de los archivos
- Rangos de valores
- Tipos de equipos
- Severidades
- Existencia de equipos
- Códigos duplicados

### GeneradorReporte

Genera los reportes diarios y el reporte final en archivos de texto.

### Simulador

Ejecuta la simulación de 30 días.

Coordina:

- Degradación diaria
- Activación de incidencias
- Cálculo de prioridad
- Ordenamiento
- Selección de equipos atendidos
- Aplicación de mantenimiento
- Generación de reportes

### SistemaMantenimiento

Coordina la lógica principal del sistema.

Administra:

- Equipos
- Incidencias
- Datos de prueba
- Carga desde archivos
- Registro manual
- Ejecución de simulación

### Menu

Maneja la interacción con el usuario mediante consola.

### main.cpp

Inicia el sistema, configura la ejecución y captura errores fatales.

---

## Patrón de diseño utilizado

El sistema utiliza el patrón Template Method.

Este patrón se aplica en la clase base Equipo.

La clase Equipo define el flujo general del mantenimiento mediante el método realizarMantenimiento().

Ese método establece el proceso general:

1. Preparar mantenimiento
2. Aplicar mantenimiento específico
3. Cerrar una incidencia activa
4. Reiniciar tiempo inactivo
5. Registrar día de atención

Las clases derivadas implementan el comportamiento específico mediante aplicarMantenimientoEspecifico().

Esto permite que todos los equipos sigan el mismo proceso general, pero que cada tipo de equipo aplique su mantenimiento de forma diferente.

---

## Polimorfismo

El sistema utiliza polimorfismo mediante la clase base Equipo.

La colección principal de equipos se maneja con std::vector<std::unique_ptr<Equipo>>.

Esto permite almacenar distintos tipos de equipos en una misma colección:

- EquipoComputo
- EquipoLaboratorio
- EquipoMedico

El uso de std::unique_ptr permite manejar memoria automáticamente y evita fugas de memoria.

---

## Upcast y Downcast

### Upcast

El sistema usa upcast al almacenar objetos derivados como punteros a la clase base Equipo.

Ejemplo conceptual:

- EquipoComputo -> Equipo
- EquipoLaboratorio -> Equipo
- EquipoMedico -> Equipo

### Downcast

El sistema usa dynamic_cast de forma segura para comprobar si un equipo pertenece a un tipo específico antes de aplicar comportamientos propios.

Ejemplos:

- EquipoComputo -> revisarSoftware()
- EquipoMedico -> calibrarSensores()

El resultado del dynamic_cast se valida antes de utilizarse.

---

## Forward declaration

El proyecto utiliza declaraciones adelantadas para evitar dependencias circulares.

Por ejemplo, en Equipo.h se usa class Incidencia.

Y en Incidencia.h se usa class Equipo.

Esto permite que ambas clases se relacionen sin generar ciclos de inclusión.

---

## Manejo de excepciones

El sistema utiliza excepciones personalizadas para controlar errores.

### ArchivoInvalidoException

Se lanza cuando un archivo no puede abrirse o crearse correctamente.

### FormatoInvalidoException

Se lanza cuando los datos ingresados o leídos tienen formato incorrecto.

### OperacionInconsistenteException

Se lanza cuando se intenta realizar una operación no válida dentro del sistema.

Ejemplos de errores controlados:

- Archivo inexistente
- Formato inválido
- Equipo duplicado
- Equipo inexistente
- Valor fuera de rango
- Simulación sin equipos
- Simulación sin incidencias

---

## Manejo de archivos

El sistema trabaja con archivos de texto.

Utiliza:

- ifstream
- ofstream
- stringstream

Los archivos se validan antes de usarse.

Si un archivo no puede abrirse, se lanza una excepción personalizada.

---

## Algoritmo propio de ordenamiento

El sistema implementa su propio algoritmo de ordenamiento: Merge Sort.

Se utiliza para ordenar equipos por:

- Prioridad
- Código

El ordenamiento por prioridad permite seleccionar los equipos más urgentes.

El ordenamiento por código permite aplicar búsqueda binaria.

---

## Búsqueda optimizada

El sistema utiliza búsqueda binaria para encontrar equipos por código.

Esta búsqueda se aplica cuando una incidencia debe asociarse a su equipo correspondiente.

Para que la búsqueda binaria funcione correctamente, primero se ordenan los equipos por código.

---

## Reportes generados

Cada reporte diario contiene:

- Estado general de la simulación
- Riesgo global del laboratorio
- Backlog pendiente
- Top prioridad
- Equipos atendidos
- Equipos pendientes de atención
- Prioridades calculadas

El reporte final contiene:

- Estado general final
- Cantidad de equipos
- Backlog pendiente final
- Riesgo global final
- Equipos pendientes de atención
- Estado final de equipos

---

## Cómo compilar

Desde CLion:

1. Abrir el proyecto
2. Esperar que CMake cargue
3. Presionar Build
4. Ejecutar el programa

Desde terminal con CMake:

cmake -S . -B build

cmake --build build

---

## Cómo ejecutar

En CLion, presionar Run.

Desde terminal, ejecutar el archivo generado dentro de la carpeta de compilación.

Al iniciar, el programa carga los datos iniciales automáticamente.

---

## Pruebas recomendadas

### Prueba 1: Verificar carga inicial

Ejecutar el programa y seleccionar la opción 6: Ver resumen cargado.

Resultado esperado:

- Equipos cargados: 100
- Incidencias cargadas: 300

### Prueba 2: Ejecutar simulación

Seleccionar la opción 5: Ejecutar simulación de 30 días.

Resultado esperado:

- Día 1 simulado correctamente
- Día 2 simulado correctamente
- ...
- Día 30 simulado correctamente

Luego revisar la carpeta Reportes.

### Prueba 3: Registrar equipo inválido

Intentar registrar un equipo con tipo inválido.

Resultado esperado:

- Error controlado por el sistema

### Prueba 4: Registrar incidencia con equipo inexistente

Intentar registrar una incidencia asociada a un equipo que no existe.

Resultado esperado:

- Error controlado por el sistema

### Prueba 5: Regenerar datos

Seleccionar la opción 1: Regenerar datos de prueba.

Resultado esperado:

- Datos regenerados y cargados correctamente

---

## Consideraciones para la entrega

Antes de entregar el proyecto, no se deben incluir carpetas generadas por el IDE o por la compilación.

No incluir:

- cmake-build-debug/
- .idea/
- .exe

Sí incluir:

- CMakeLists.txt
- main.cpp
- README.md
- includes/
- src/

Las carpetas Archivos y Reportes se generan automáticamente si no existen.

---

## Autor

Chris Alberto Martínez Sánchez

Curso: Programación II  
Universidad Nacional de Costa Rica
