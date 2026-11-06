# TEORIA (ESTRUCTURAS (GENERAL) Y ESTRUCTURAS ESTATICAS)

### -->  Son tipos de datos definidos por el usuario [AGRUPADOS BAJO UN SOLO NOMBRE]
<div align="center">
  <img width="1733" height="642" alt="Que es un struct" src="https://github.com/user-attachments/assets/2c89e95b-6702-4ec6-b0db-1c1ddda98b44" />
</div>

#### (esto fue sacado de las diapositivas del profe ERASMO)

# 🔨 Implementacion de la struct

<div align="center">
  <img src="../Assets/Declaracion de struct y uso.jpg"
       alt="Guía visual de Struct y su uso "
       width="100%">
</div>

# 📓 Tipos de uso con struct
  ## IMPRESION
  ### Para IMPRESION (const struct Alumno&)
  ## LECTURA
  ### Para LECTURA (struct Alumno) (GENERAS UNA COPIA) Se usa cuando la estructura es declarada interamente (Pues necesitas la posicion de lectura)
  ### Para LECTURA (struct Alumno&) Se usa cuando la estructura es declarada antes de invocar la función que depende de la estructura

<div align="center">
  <img src="../Assets/Uso de parametros con struct.png"
       alt="Guía visual de uso de parametros para struct"
       width="100%">
</div>

<div align="center">
  <img src="../Assets/Impacto de declaracion interna o externa de una STRUCT.png"
       alt="Guía visual declaracion INTERNA o EXTERNA"
       width="100%">
</div>




## * Si la estructura no es un puntero, simplemente no se le declara memoria y se puede trabajar como "."

## * Si la estructura es un puntero, se le debe asignar memoria con "new" además se de trabajar con "->" (si presionas punto se transfomra automaticamente)

# ESTRUCTURAS ANIDADAS
