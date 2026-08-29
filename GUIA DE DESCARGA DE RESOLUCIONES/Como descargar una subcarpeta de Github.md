# 📥 Descargar una subcarpeta de GitHub

> ¿Solo necesitas una resolución, laboratorio o conjunto de archivos y no quieres descargar todo el repositorio?

GitHub permite descargar el repositorio completo mediante **Code → Download ZIP**, pero actualmente no ofrece una opción nativa para descargar únicamente una subcarpeta.

Para estos casos podemos utilizar una herramienta como **GitZip**, que permite seleccionar una carpeta específica de un repositorio público y descargarla como `.zip`.

---

## 🎯 Ejemplo

Supongamos que solamente quieres descargar:

```text
LAB/
└── LAB 04/
    └── Resolucion/
```

y **no** todo el repositorio `TP-`.

En lugar de hacer:

```text
Code
 ↓
Download ZIP
 ↓
Descargar TODO TP-
```

podemos descargar solamente:

```text
LAB 04/
```

---

# 🟢 Método recomendado — GitZip

## 1. Abre la carpeta que quieres descargar

Primero entra al repositorio de GitHub y navega normalmente hasta la carpeta que quieres descargar.

Por ejemplo:

```text
GitHub
  ↓
TP-
  ↓
LAB
  ↓
LAB 04
```

La URL de tu navegador tendrá una estructura similar a:

```text
https://github.com/usuario/repositorio/tree/main/ruta/de/la/carpeta
```

> 💡 **Importante:** debes copiar la URL de la **carpeta**, no la URL del repositorio principal.

---

## 2. Copia la URL de la carpeta

Cuando estés dentro de la carpeta que quieres descargar:

**Ctrl + L**

para seleccionar la dirección del navegador.

Después:

**Ctrl + C**

para copiarla.

Ejemplo:

```text
https://github.com/rren-ato/TP-/tree/main/LAB/LAB%2004
```

---

## 3. Abre GitZip

Puedes utilizar:

**[🌐 GitZip](https://gitzip.org/)**

GitZip está diseñado específicamente para descargar subdirectorios o archivos individuales de repositorios de GitHub.

También existe una versión web alternativa:

**[🌐 Download Directory](https://download-directory.github.io/)**

Esta herramienta permite pegar directamente la URL de una carpeta de GitHub y descargar su contenido.

---

## 4. Pega la URL

En GitZip, pega la dirección que copiaste anteriormente.

```text
┌─────────────────────────────────────────────────────┐
│ https://github.com/rren-ato/TP-/tree/main/LAB/... │
└─────────────────────────────────────────────────────┘

                    [ Download ]
```

Después inicia la descarga.

---

## 5. Espera a que se genere el ZIP

La herramienta procesará los archivos que se encuentran dentro de la carpeta seleccionada.

No necesitas descargar:

```text
❌ Todo el repositorio
❌ Otras evaluaciones
❌ Otros laboratorios
❌ Archivos que no necesitas
```

Solamente:

```text
✅ La carpeta seleccionada
```

---

## 6. Extrae el archivo

Una vez descargado el `.zip`:

1. Ve a tu carpeta de **Descargas**.
2. Busca el archivo `.zip`.
3. Haz clic derecho.
4. Selecciona **Extraer todo...**.

Ahora tendrás solamente los archivos correspondientes a la carpeta seleccionada.

---

# 🟣 Ejemplo aplicado a este repositorio

Si quieres descargar solamente una resolución de `TP-`, imagina que tienes:

```text
TP-/
│
├── LAB/
│   │
│   ├── LAB 01/
│   ├── LAB 02/
│   ├── LAB 03/
│   └── LAB 04/
│       │
│       ├── Enunciado.pdf
│       ├── datos.txt
│       └── Resolucion/
│           ├── main.cpp
│           └── Utils.hpp
│
├── LAB 05/
└── ...
```

Si solamente necesitas:

```text
LAB 04/Resolucion/
```

no es necesario descargar todo:

```text
TP-.zip
```

Puedes abrir directamente:

```text
LAB
 ↓
LAB 04
 ↓
Resolucion
```

y utilizar la URL de esa carpeta con GitZip.

El resultado será aproximadamente:

```text
Resolucion.zip
│
├── main.cpp
└── Utils.hpp
```

---

# ⚠️ Consideraciones

### 📌 El repositorio debe ser accesible

Estas herramientas están pensadas principalmente para repositorios públicos. GitZip también contempla autenticación mediante un Personal Access Token para determinados escenarios y para evitar límites de la API.

### 📌 No confundas archivo con carpeta

Si quieres descargar:

```text
📁 Resolucion/
```

copia la URL de la carpeta.

Si quieres descargar:

```text
📄 main.cpp
```

puedes utilizar directamente la opción de descarga del archivo de GitHub o descargarlo individualmente.

### 📌 GitZip no es Git

Esto:

```text
GitZip
```

sirve para obtener una **copia de los archivos**.

No mantiene:

* historial de commits;
* ramas;
* configuración Git;
* conexión con el repositorio.

Si quieres trabajar con Git y mantener el historial/versionado, entonces deberías clonar el repositorio o utilizar otras técnicas de Git.

---

# 🧭 ¿Qué método debería utilizar?

| Necesidad                       | Método recomendado                |
| ------------------------------- | --------------------------------- |
| 📦 Todo el repositorio          | `Code → Download ZIP`             |
| 📁 Una subcarpeta               | **GitZip**                        |
| 📄 Un archivo                   | Descargar el archivo desde GitHub |
| 💻 Trabajar con Git             | `git clone`                       |
| 🔀 Contribuir al proyecto       | Fork + clone                      |
| 📚 Solo estudiar una resolución | **GitZip**                        |

---

## 💡 Recomendación para `TP-`

Si solamente quieres revisar una resolución, **no necesitas descargar todo el repositorio**.

La idea es:

```text
                    TP-
                     │
                     ▼
              📁 Laboratorios
                     │
                     ▼
                📁 LAB 04
                     │
                     ▼
               📁 Resolución
                     │
                     ▼
                  🔗 URL
                     │
                     ▼
                 GitZip
                     │
                     ▼
              📦 Resolucion.zip
```

De esta manera puedes obtener únicamente el material que necesitas sin descargar el resto del repositorio.
