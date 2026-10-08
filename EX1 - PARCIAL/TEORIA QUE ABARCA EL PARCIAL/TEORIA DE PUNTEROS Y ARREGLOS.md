# Array vs Puntero

Explicación rápida de la diferencia real entre **arrays** y **punteros** (basado en la teoría de clase).

<div align="center">
  <img src="../Assets/Arreglo vs Puntero.jpg"
       alt="Arreglos y Punteros"
       width="100%">
</div>

---

## ¿Qué es un Array realmente?

Un **array** es:

- Una **agrupación de elementos contiguos** del mismo tipo en memoria.
- El **nombre del array** actúa como un **puntero constante** al primer elemento.
- Tiene **capacidad fija** (espacio reservado) y **longitud** (elementos usados).

```c
int numeros[5] = {10, 20, 30, 40, 50};

// numeros  →  dirección del primer elemento (0x100)
// numeros[0]  →  10
// numeros[1]  →  20
```

**Importante:**  
No se puede reasignar el nombre del array:

```c
numeros = otroArray;   // ❌ ERROR
```

---

## ¿Qué es un Puntero?

Un **puntero** es simplemente una **variable que guarda una dirección de memoria**.

```c
int *ptr = numeros;    // ptr guarda la dirección 0x100
ptr = &otraVariable;   // ✅ se puede reasignar
ptr = NULL;            // ✅ puede no apuntar a nada
```

- Se puede reasignar libremente.
- Puede apuntar a cualquier cosa (o a nada = `NULL`).
- Soporta **aritmética de punteros**: `ptr + 1` avanza según el tamaño del tipo.

---

## Resumen clave

| Concepto              | Array                          | Puntero                          |
|-----------------------|--------------------------------|----------------------------------|
| Qué es                | Bloque contiguo de memoria     | Variable que guarda una dirección |
| Nombre                | Puntero **constante**          | Variable normal                  |
| Reasignar             | ❌ No se puede                 | ✅ Sí se puede                   |
| Tamaño                | Tiene capacidad fija           | Solo guarda una dirección        |
| Uso similar           | `arr[i]` y `*(ptr + i)`        | Igual                            |

> **Frase clave:**  
> El nombre del array es un puntero al primer elemento,  
> pero el array **no es** un puntero.  
> El array es el **bloque de memoria** + el nombre actúa como puntero.

---
