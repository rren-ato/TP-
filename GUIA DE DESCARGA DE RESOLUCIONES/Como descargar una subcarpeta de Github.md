# 📥 Descargar una subcarpeta de GitHub

> ¿Solo necesitas una resolución, laboratorio o conjunto de archivos?
>
> **No necesitas descargar todo el repositorio.**

GitHub permite descargar un repositorio completo mediante `Code → Download ZIP`, pero no ofrece directamente una opción para descargar una sola subcarpeta.

Para estos casos podemos utilizar **[Download Directory](https://download-directory.github.io/)**, una herramienta sencilla que permite descargar directamente el contenido de una carpeta de un repositorio público de GitHub.

---

## 🎯 ¿Cuándo utilizar esto?

Por ejemplo, si el repositorio contiene:

```text
TP-/
│
├── LAB/
│   ├── LAB 01/
│   ├── LAB 02/
│   ├── LAB 03/
│   ├── LAB 04/
│   │   ├── Enunciado.pdf
│   │   ├── datos.txt
│   │   └── Resolucion/
│   │       ├── main.cpp
│   │       └── Utils.hpp
│   └── ...
│
└── ...

## 💡 Recomendación para `TP-`

Si solamente quieres revisar una resolución, **no necesitas descargar todo el repositorio**.

La idea es:

            TP-
             │
             ▼
            LAB
             │
             ▼
          LAB 04
             │
             ▼
         Resolucion
             │
             ▼
        Copiar URL
             │
             ▼
     Download Directory
             │
             ▼
      📦 Resolucion.zip
```

De esta manera puedes obtener únicamente el material que necesitas sin descargar el resto del repositorio.
