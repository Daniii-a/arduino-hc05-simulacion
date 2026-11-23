/*
 * Proyecto: Control de LEDs por enlace serial / Bluetooth (HC-05)
 * Placa: Arduino UNO
 * Pines de salida:
 *   - LED Verde: Pin digital 2 (con resistencia limitadora de 220 ohmios)
 *   - LED Rojo:  Pin digital 3 (con resistencia limitadora de 220 ohmios)
 * Velocidad serial: 9600 baudios
 * Enfoque: Lectura no bloqueante con millis() sin uso de delay().
 */

const int PIN_LED_VERDE = 2;
const int PIN_LED_ROJO  = 3;

// Intervalo no bloqueante (en ms) para reporte de estado o telemetria si se requiere
const unsigned long INTERVALO_TELEMETRIA_MS = 5000;
unsigned long ultimoReporteMs = 0;

bool estadoLedVerde = false;
bool estadoLedRojo  = false;

void aplicarEstadosLeds() {
  digitalWrite(PIN_LED_VERDE, estadoLedVerde ? HIGH : LOW);
  digitalWrite(PIN_LED_ROJO,  estadoLedRojo  ? HIGH : LOW);
}

void imprimirEstadoActual() {
  Serial.print("Estado actual -> Verde (Pin 2): ");
  Serial.print(estadoLedVerde ? "ENCENDIDO (HIGH)" : "APAGADO (LOW)");
  Serial.print(" | Rojo (Pin 3): ");
  Serial.println(estadoLedRojo ? "ENCENDIDO (HIGH)" : "APAGADO (LOW)");
}

void procesarComando(char comando) {
  // Ignorar caracteres de control de fin de linea
  if (comando == '\n' || comando == '\r') {
    return;
  }

  Serial.print("Comando recibido: '");
  Serial.print(comando);
  Serial.println("'");

  switch (comando) {
    case '1':
      estadoLedVerde = true;
      aplicarEstadosLeds();
      Serial.println("Accion: LED Verde ENCENDIDO.");
      break;

    case '0':
      estadoLedVerde = false;
      aplicarEstadosLeds();
      Serial.println("Accion: LED Verde APAGADO.");
      break;

    case '2':
      estadoLedRojo = true;
      aplicarEstadosLeds();
      Serial.println("Accion: LED Rojo ENCENDIDO.");
      break;

    case '3':
      estadoLedRojo = false;
      aplicarEstadosLeds();
      Serial.println("Accion: LED Rojo APAGADO.");
      break;

    case 'T':
    case 't':
      estadoLedVerde = true;
      estadoLedRojo  = true;
      aplicarEstadosLeds();
      Serial.println("Accion: Ambos LEDs ENCENDIDOS.");
      break;

    case 'A':
    case 'a':
      estadoLedVerde = false;
      estadoLedRojo  = false;
      aplicarEstadosLeds();
      Serial.println("Accion: Ambos LEDs APAGADOS.");
      break;

    case '?':
      imprimirEstadoActual();
      break;

    default:
      Serial.println("Aviso: Comando no valido. Use 1, 0, 2, 3, T, A o ?.");
      break;
  }
}

void setup() {
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);

  aplicarEstadosLeds();

  Serial.begin(9600);
  ultimoReporteMs = millis();

  Serial.println("====================================================");
  Serial.println("Sistema iniciado - Enlace serial a 9600 baudios");
  Serial.println("Comandos: 1 (Verde ON), 0 (Verde OFF), 2 (Rojo ON),");
  Serial.println("          3 (Rojo OFF), T (Todos ON), A (Apagar), ? (Estado)");
  Serial.println("====================================================");
  imprimirEstadoActual();
}

void loop() {
  unsigned long ahoraMs = millis();

  // Procesar todos los bytes disponibles en el buffer serial sin bloquear
  while (Serial.available() > 0) {
    char datoEntrante = Serial.read();
    procesarComando(datoEntrante);
  }

  // Ejemplo de tarea periodica no bloqueante con millis() cada 5 segundos
  if (ahoraMs - ultimoReporteMs >= INTERVALO_TELEMETRIA_MS) {
    ultimoReporteMs = ahoraMs;
    // Descomenta la siguiente linea si deseas registrar lecturas periodicas en el monitor:
    // imprimirEstadoActual();
  }
}
