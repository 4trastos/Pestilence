# Pestilence — Project UNIX @ 42Network

> *"AND HIS NAME IS ......"*

## 📋 Descripción

**Pestilence** es la evolución de Famine. Mantiene la misma funcionalidad de infección de binarios ELF64 pero añade tres capas de protección:

- **Anti-proceso** — no ejecuta si un proceso específico está activo
- **Anti-debug** — detecta si está siendo ejecutado bajo un debugger
- **Ofuscación** — la rutina de infección es difícil de leer y entender

## 🎯 Objetivos

- Implementar detección de procesos activos
- Implementar detección de debugger
- Ofuscar la rutina de infección para dificultar el análisis

## ⚙️ Funcionamiento

```
./Pestilence
```

**Sin proceso "test" activo y sin debugger:**
```bash
pgrep "test"          # sin output
./Pestilence          # infecta
strings /tmp/test/ls | grep "davgalle"
# Pestilence version 1.0 (c)oded by davgalle
```

**Con proceso "test" activo:**
```bash
pgrep "test"          # 22987
./Pestilence          # no infecta, sin output
strings /tmp/test/ls | grep "davgalle"
# sin output
```

**Bajo debugger:**
```bash
gdb -q ./Pestilence
(gdb) run
# DEBUGGING..
# [Inferior 1 (process 2683) exited with code 01]
strings /tmp/test/ls | grep "davgalle"
# sin output
```

## 🔬 Conceptos técnicos

| Concepto | Descripción |
|----------|-------------|
| `ptrace(PTRACE_TRACEME)` | Detección de debugger |
| `/proc` | Lectura de procesos activos |
| Ofuscación | XOR, funciones señuelo, flujo de control alterado |
| ELF64 | Mismo formato que Famine |
| `mmap` | Mapeo de ficheros en memoria |

## 🛡️ Restricciones

- Solo actúa en `/tmp/test` y `/tmp/test2`
- Un binario solo puede infectarse una vez
- Sin output en stdout ni stderr bajo ninguna circunstancia
- Escrito en C, C++ o ASM únicamente
- Requiere VM con Linux 64 bits

## 🔧 Compilación

```bash
make
```

## 🐳 Docker (desarrollo)

```bash
docker run -it --rm \
  -v "$(pwd):/workspace" \
  -w /workspace \
  debian:bullseye \
  bash -c "apt update -qq && apt install -y build-essential binutils && bash"
```

## 💻 Entorno

- Linux 64 bits (Debian 7.0+)
- VM obligatoria para evaluación

## 📚 Lo que aprendes

Pestilence introduce conceptos de **evasión de análisis** — las mismas técnicas que usa el malware real para evitar ser detectado y analizado. La ofuscación del código es un campo entero de la seguridad ofensiva.

---

*Proyecto realizado en el marco del cursus de ciberseguridad de 42Network Madrid.*