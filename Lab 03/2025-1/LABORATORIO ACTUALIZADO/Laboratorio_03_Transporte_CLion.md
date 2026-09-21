# TÉCNICAS DE PROGRAMACIÓN — LABORATORIO CALIFICADO (práctica, versión CLion)

**Basado en:** Tercer Laboratorio Calificado, semestre 2025-1 (versión original en NetBeans, con archivos `.txt`).
**Adaptado a:** entorno CLion, con archivos de entrada en CSV y JSON Lines, y reporte de salida en JSON.

---

## Contexto del problema

El Ministerio de Transportes lleva un registro de las infracciones de tránsito cometidas por diferentes
empresas de transporte. Esta información se encuentra distribuida en tres archivos:

1. `TablaDeInfracciones.txt` — catálogo de tipos de infracción (sin cambios respecto al enunciado original).
2. `EmpresasRegistradas.csv` — empresas registradas y sus vehículos (**nuevo formato CSV**).
3. `InfraccionesCometidas.jsonl` — infracciones cometidas por cada vehículo (**nuevo formato JSON Lines**).

Se pide desarrollar un proyecto en C++ (CLion) que lea estos tres archivos, cruce la información y genere
un **reporte de salida en formato JSON**.

---

## 1. `TablaDeInfracciones.txt`

Sin cambios respecto al original: texto plano, separado por tabulaciones, una infracción por línea.

```
L3001	158.33	Circular en las vias publicas urbanas o de acceso restringido sin cinturon de seguridad
G2007	425.23	No conducir por el carril de extremo derecho de la calzada un vehiculo de transporte publico
M1002	950.60	Participar en una competencia de velocidad no autorizada en la via publica
```

Cada línea contiene: **código de infracción** (una letra + número: `L`=leve, `G`=grave, `M`=muy grave),
**monto de la multa** y **descripción**.

---

## 2. `EmpresasRegistradas.csv`

Cambia de `.txt` a **CSV**, y de "una fila por empresa con placas variables" a **una fila por vehículo**.
Esto es necesario porque, con el nuevo formato de placa (ver más abajo), el tipo de vehículo ya no se
puede inferir de la placa y debe declararse explícitamente.

```
dni,representanteLegal,distrito,placa,tipo
79672079,contreras/chang/johana-cinthia,Chorrillos,WDA433,PEQUENO
79672079,contreras/chang/johana-cinthia,Chorrillos,EZD819,MEDIANO
79672079,contreras/chang/johana-cinthia,Chorrillos,PBA133,PEQUENO
77763722,farfan/salazar/margot,La_Molina,SVA838,PEQUENO
```

Columnas: `dni`, `representanteLegal` (apellidos/nombres separados por `/` y `-`), `distrito`
(palabras separadas por `_`), `placa`, `tipo` (`PEQUENO`, `MEDIANO` o `GRANDE`).

Una misma empresa (mismo `dni`) puede aparecer en varias filas consecutivas, una por cada vehículo
de su propiedad.

**Formato de placa:** ahora es **3 letras + 3 números** (ej. `WDA433`, `EZD819`), sin guion.

**Formateo de nombres:** los nombres del representante legal y el distrito deben mostrarse con la
primera letra de cada palabra en mayúscula y el resto en minúscula, reemplazando además los
caracteres `/`, `-` y `_` por un espacio en blanco (igual que en el enunciado original).

---

## 3. `InfraccionesCometidas.jsonl`

Cambia de `.txt` a **JSON Lines**: un objeto JSON completo por línea, **sin** corchetes envolventes
ni comas entre líneas. Cada línea agrupa todas las infracciones cometidas por una misma placa:

```
{"placa": "WDA433", "infracciones": [{"fecha": "02/02/2022", "codigo": "M1002"}]}
{"placa": "SVA838", "infracciones": [{"fecha": "21/11/2022", "codigo": "G2005"}, {"fecha": "02/04/2022", "codigo": "G2016"}, {"fecha": "10/07/2023", "codigo": "L3009"}]}
```

Cada objeto tiene dos campos: `placa` y `infracciones` (arreglo de objetos, cada uno con `fecha` y
`codigo`). Una placa puede tener cero, una o varias infracciones registradas.

Es posible que el código de alguna infracción cometida **no exista** en `TablaDeInfracciones.txt`;
en ese caso, el reporte debe indicarlo (ver sección "encontrado" más abajo) y el programa debe
continuar sin detenerse.

---

## 4. Reporte de salida (JSON)

El programa debe generar un archivo `Reporte.json` con la siguiente estructura (indentado, para
que sea legible por una persona):

```json
{
  "titulo": "MINISTERIO DE TRANSPORTE",
  "subtitulo": "MULTAS IMPUESTAS A LAS COMPANIAS",
  "companias": [
    {
      "numero": 1,
      "representanteLegal": "Contreras Chang Johana Cinthia",
      "dni": "79672079",
      "distrito": "Chorrillos",
      "vehiculos": [
        {
          "numero": 1,
          "placa": "WDA433",
          "tipo": "PEQUENO",
          "infracciones": [
            {
              "numero": 1,
              "fecha": "02/02/2022",
              "codigoInfraccion": 1002,
              "gravedad": "MUY GRAVE",
              "multa": 950.60,
              "descripcion": "Participar en una competencia de velocidad no autorizada en la via publica"
            }
          ]
        },
        {
          "numero": 2,
          "placa": "EZD819",
          "tipo": "MEDIANO",
          "infracciones": [
            {
              "numero": 1,
              "fecha": "07/01/2022",
              "codigoInfraccion": 2023,
              "gravedad": "GRAVE",
              "multa": 410.35,
              "descripcion": "Circular con las puertas del vehiculo abiertas"
            }
          ]
        }
      ],
      "resumen": {
        "faltasLeves": { "cantidad": 0, "montoPagado": 0.0 },
        "faltasGraves": { "cantidad": 1, "montoPagado": 410.35 },
        "faltasMuyGraves": { "cantidad": 1, "montoPagado": 950.60 },
        "pagoTotal": 1360.95
      }
    }
  ],
  "estadisticasGlobales": {
    "companiaConMayorPago": { "dni": "...", "totalPagado": 0.0 },
    "companiaConMenorPago": { "dni": "...", "totalPagado": 0.0 }
  }
}
```

**Caso de código no encontrado en el catálogo:**

```json
{
  "numero": 3,
  "fecha": "07/09/2024",
  "codigoInfraccion": 2999,
  "encontrado": false,
  "mensaje": "No se encontro esa infraccion"
}
```

Vehículos sin ninguna infracción registrada pueden omitirse del reporte o incluirse con un arreglo
`infracciones` vacío (decisión de diseño libre, pero debe ser consistente en todo el programa).

---

## Consideraciones para la implementación

- Debe usarse obligatoriamente `fstream` para leer y escribir los archivos.
- La lectura de números (montos, códigos, edades, etc.) debe hacerse como tal, no como texto.
- El código debe organizarse en `main.cpp` + `Bibliotecas/FuncionesAuxiliares.h` y `.cpp`, sin
  variables globales y sin funciones implementadas dentro de `main.cpp`.
- Cuidado con los finales de línea CRLF (`\r\n`) en los archivos de texto/CSV.
- Se sugiere separar claramente las funciones de: (1) parseo de cada archivo, (2) cruce de datos,
  (3) generación del reporte JSON, (4) formateo de nombres/distritos.

---

## Archivos de entrada de ejemplo

Junto con este enunciado se entregan tres archivos de ejemplo, generados a partir de datos reales
del laboratorio original, ya migrados al nuevo formato:

- `TablaDeInfracciones.txt`
- `EmpresasRegistradas.csv`
- `InfraccionesCometidas.jsonl`
