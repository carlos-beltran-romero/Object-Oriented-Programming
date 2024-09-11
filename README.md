# Proyecto P1 de Manejo de Cadenas y Fechas en C++

Este proyecto implementa dos clases principales en C++: `Cadena` y `Fecha`, que permiten trabajar con cadenas de caracteres y fechas de manera robusta y personalizada, utilizando sobrecarga de operadores y manejo de excepciones.

## Estructura de Clases

### 1. **Clase `Cadena`**
   La clase `Cadena` permite manejar cadenas de caracteres (`strings`) con una implementación propia y ofrece una serie de funcionalidades para manipular y gestionar cadenas.

#### Funcionalidades:
   - **Constructores**:
     - Crear una cadena a partir de un tamaño y un carácter.
     - Copiar una cadena desde otra instancia.
     - Construir a partir de un literal de caracteres (`const char*`).
     - Constructor de movimiento.
   - **Operadores sobrecargados**:
     - Asignación (`=`) y asignación por movimiento.
     - Operador `+=` para concatenar cadenas.
     - Operador `[]` para acceso a caracteres individuales.
   - **Manejo de errores**:
     - El método `at()` lanza excepciones de tipo `std::out_of_range` para accesos fuera de rango.
   - **Otras características**:
     - Manipulación de la longitud de la cadena.
     - Comparación de cadenas.

### 2. **Clase `Fecha`**
   La clase `Fecha` permite trabajar con fechas de manera segura y con múltiples validaciones para garantizar la corrección de los datos ingresados.

#### Funcionalidades:
   - **Constructores**:
     - Acepta día, mes y año como parámetros.
     - Permite construir una fecha a partir de una cadena de caracteres.
   - **Operadores sobrecargados**:
     - Incremento (`++`) y decremento (`--`) en versiones pre- y post-incremento.
     - Operadores de comparación (`<`, `<=`, `==`, `>`, `>=`, `!=`).
     - Operadores aritméticos para sumar o restar días a la fecha.
   - **Manejo de excepciones**:
     - La clase interna `Invalida` gestiona errores relacionados con fechas no válidas.
   - **Rangos válidos**:
     - El año debe estar entre 1902 y 2037.

El proyecto P4 cuenta con funcionalidades más destacadas a visualizar.
