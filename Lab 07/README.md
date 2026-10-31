## 🧠 Arreglo de Cadena de caracteres (uso de char**)
### --> Se permite el uso de cstring y ctype

### 📖 Guía visual

<div align="center">
  <img src="../Assets/Arreglos de Cadena de Caracteres y Cstring.jpg"
       alt="Guía visual de arreglos de Cadena de Caracteres"
       width="100%">
</div>

En particular en leerCadena y AsignarCadena...
El buffer y el str (o cadena), son valores locales, el buffer es un arreglo local y el str (o cadena) es un puntero, se usa un momento como puntero a memoria
Sin embargo el puntero solo sirve para guardar el arreglo en el heap (en un espacio de memoria); sin embargo el puntero en si es simplemente local

## 🧠 Liberacion de memoria (delete[])
Liberación de memoria depende si tienes un arreglo estático, debes eliminar la cadena o valor con un for (una iteración), si es un arreglo dinamico meramente se elimina la memoria de forma directa (sin considerar "[i]" posiciones)
<div align="center">
  <img width="1123" height="476" alt="image" src="https://github.com/user-attachments/assets/993bc0e7-21e1-4576-a1e8-4c8105b53c95" />
</div>

## 🧠 Lógica de puntero a cadenas
<div align="center">
  <img width="1185" height="467" alt="image" src="https://github.com/user-attachments/assets/62de1729-a583-4b08-aae3-73396867f720" />
</div>
