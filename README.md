# Control de LEDs por Enlace Serial / Bluetooth (HC-05) en Arduino UNO

Repositorio correspondiente a la simulación y documentación del circuito de control de dos LEDs (verde y rojo) mediante comandos recibidos por enlace serial a `9600` baudios en Arduino UNO, tomando como referencia el montaje con módulo Bluetooth HC-05.

## Componentes y conexiones

- **Microcontrolador:** Arduino UNO
- **Módulo de referencia:** HC-05 Bluetooth Module (componente visual/estático en el entorno de simulación)
- **Actuadores:**
  - **LED Verde:** Pin digital `2` con resistencia limitadora de `220 Ω` y conexión a `GND`
  - **LED Rojo:** Pin digital `3` con resistencia limitadora de `220 Ω` y conexión a `GND`
- **Comunicación serial:** `9600` baudios (mediante Monitor/Consola Serie para la validación de comandos)

## Comandos disponibles

Envía los siguientes caracteres por el Monitor Serie (`9600` baudios):

| Comando | Acción |
| :--- | :--- |
| `1` | Enciende el LED Verde (Pin `2` en `HIGH`) |
| `0` | Apaga el LED Verde (Pin `2` en `LOW`) |
| `2` | Enciende el LED Rojo (Pin `3` en `HIGH`) |
| `3` | Apaga el LED Rojo (Pin `3` en `LOW`) |
| `T` / `t` | Enciende ambos LEDs |
| `A` / `a` | Apaga ambos LEDs |
| `?` | Muestra el estado actual de ambos LEDs en la consola |

## Estructura del repositorio

- `control_leds_serial.ino`: Código fuente en C++ con programación no bloqueante basada en `millis()`.
- `README.md`: Documentación general del proyecto, conexiones y comandos de prueba.
- Capturas y evidencias de simulación (circuito, código y respuestas del Monitor Serie).

## Notas de simulación

- En el simulador utilizado, el módulo **HC-05** actúa como elemento estático de diagrama (no simula transmisión RF Bluetooth real), por lo que las pruebas de envío y recepción de datos se realizan directamente a través del enlace serial a `9600` baudios.
- La lógica del *sketch* evita el uso de `delay()` bloqueante mediante `millis()`, manteniendo la lectura de comandos receptiva.
