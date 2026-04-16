# SPIKE ARQUITECTONICO — HydroSense

Documento de investigacion tecnica para validar las decisiones de arquitectura antes de iniciar el desarrollo del sistema completo.

---

## SPIKE-01: Lectura estable de sensores de humedad y conectividad a Firebase

### Informacion general

| Campo | Detalle |
|-------|---------|
| ID | SPIKE-01 |
| Release | Release 1 (Semana 2) |
| Responsable | Todo el equipo |
| Duracion estimada | 3 a 4 dias |
| Prioridad | Critica |

---

### Contexto y problema

Antes de construir el sistema completo, es necesario validar dos componentes tecnicos que representan la mayor incertidumbre del proyecto:

1. El ADC integrado del ESP32 tiene caracteristicas no lineales conocidas y los pines ADC2 son incompatibles con WiFi activo. Se desconoce si las lecturas de los sensores de humedad del suelo seran lo suficientemente estables para tomar decisiones de riego confiables.

2. No se ha verificado si el ESP32 puede publicar datos a Firebase via MQTT de forma confiable en un entorno de red domestica, ni cuanto recurso de memoria consume este proceso.

---

### Hipotesis

**Hipotesis 1:** Promediando 20 muestras consecutivas del ADC con 10 ms de separacion entre cada una, se puede reducir el ruido a una desviacion estandar menor a 50 unidades ADC, lo que equivale a menos del 2 % de error en humedad. Ese nivel de precision es suficiente para diferenciar los tres estados del sistema.

**Hipotesis 2:** Usando la libreria PubSubClient con un broker MQTT gratuito (HiveMQ Cloud), el ESP32 puede entregar mas del 95 % de los mensajes con una latencia promedio menor a 500 ms, y el consumo de RAM adicional sera menor a 60 KB.

---

### Experimento 1: Estabilidad del sensor

#### Configuracion del banco de pruebas

```
ESP32 DevKit v1
├── GPIO34  --->  Sensor YL-69 numero 1
├── GPIO35  --->  Sensor capacitivo v1.2 (para comparacion)
└── GND / 3.3V  --->  Alimentacion de los sensores
```

#### Codigo de prueba

```cpp
#include <Arduino.h>

const int PIN_SENSOR = 34;
const int N_MUESTRAS = 20;
const int ADC_SECO     = 3400;
const int ADC_SATURADO = 900;

float leerHumedad(int pin) {
  long suma = 0;
  for (int i = 0; i < N_MUESTRAS; i++) {
    suma += analogRead(pin);
    delay(10);
  }
  int promedio = suma / N_MUESTRAS;
  float pct = map(promedio, ADC_SECO, ADC_SATURADO, 0, 100);
  return constrain(pct, 0.0f, 100.0f);
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
}

void loop() {
  for (int i = 0; i < 50; i++) {
    int raw = analogRead(PIN_SENSOR);
    float h  = leerHumedad(PIN_SENSOR);
    Serial.printf("Muestra %d | RAW: %d | Humedad: %.1f%%\n", i + 1, raw, h);
    delay(1000);
  }
  Serial.println("--- FIN DEL TEST ---");
  while (true);
}
```

#### Condiciones a probar

| Condicion | Descripcion | Muestras |
|-----------|-------------|----------|
| C1 — Seco | Tierra sin regar durante 48 h | 50 |
| C2 — Humedo | Tierra regada 1 h antes | 50 |
| C3 — Saturado | Agua visible en la superficie | 50 |
| C4 — WiFi activo | Repetir C2 con WiFi conectado | 50 |

#### Resultados esperados

| Condicion | Rango ADC esperado | Humedad (%) | Desv. std esperada |
|-----------|-------------------|-------------|-------------------|
| Seco | 3.000 a 3.500 | 0 a 20 % | < ±60 |
| Humedo | 1.500 a 2.200 | 38 a 62 % | < ±40 |
| Saturado | 800 a 1.200 | 80 a 100 % | < ±30 |
| WiFi activo | Sin diferencia con ADC1 | — | Similar a C2 |

---

### Experimento 2: Conectividad MQTT a Firebase

#### Codigo de prueba

```cpp
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClient   espClient;
PubSubClient client(espClient);

void publicarLectura(float humedad) {
  StaticJsonDocument<200> doc;
  doc["planta_id"] = "maceta_01";
  doc["humedad"]   = humedad;
  doc["timestamp"] = millis();

  char buffer[200];
  serializeJson(doc, buffer);

  unsigned long t0 = millis();
  bool ok = client.publish("hydrosense/lecturas", buffer);
  Serial.printf("[MQTT] %s | Latencia: %lums\n",
                ok ? "OK" : "FAIL", millis() - t0);
}
```

**Procedimiento:** Publicar 100 mensajes con intervalo de 5 s durante 10 minutos. Registrar mensajes enviados, confirmados y latencia de cada uno.

---

### Criterios de exito y fracaso

| Criterio | Exito | Fracaso |
|----------|-------|---------|
| Desviacion estandar en C2 (humedo) | < ±50 ADC | > ±100 ADC |
| Diferencia distinguible entre C1 y C3 | > 1.500 ADC | < 800 ADC |
| Estabilidad con WiFi activo (ADC1) | Sin cambio notable | Varianza mayor al doble |
| Tasa de entrega MQTT | > 95 % | < 90 % |
| Latencia promedio MQTT | < 500 ms | > 1.000 ms |
| Consumo de RAM adicional | < 60 KB | > 100 KB |

---

### Riesgos identificados

| Riesgo | Probabilidad | Impacto | Plan de mitigacion |
|--------|-------------|---------|-------------------|
| ADC con ruido excesivo | Media | Alto | Aumentar N_MUESTRAS a 50; aplicar filtro IIR |
| Sensor resistivo se oxida rapidamente | Alta | Medio | Migrar a sensor capacitivo desde el prototipo final |
| Rango ADC insuficiente para los tres estados | Baja | Alto | Ajustar atenuacion o agregar divisor de voltaje |
| MQTT consume demasiada RAM | Baja | Alto | Evaluar Firebase REST API como alternativa |
| Perdida de conexion frecuente | Media | Medio | Backoff exponencial + watchdog timer en el firmware |

---

### Registro de resultados

Completar esta seccion al finalizar el experimento.

**Sensor seleccionado:** _______________

**N de muestras usado:** _______________

**Umbrales definidos:**
- SECO: humedad < _____ %
- NORMAL: entre _____ % y _____ %
- SATURADO: humedad > _____ %

**Conectividad:**
- Tasa de entrega medida: _____ %
- Latencia promedio: _____ ms
- RAM adicional usada: _____ KB

**Conclusion:** El sistema es viable con el diseno actual / Requiere los siguientes ajustes: _______________

---

### Formato del reporte final

Al concluir el spike, los resultados se incorporan a la seccion "Reporte del spike" del README principal. El reporte debe incluir:

- Pregunta que se buscaba responder
- Metodologia del experimento
- Tabla con resultados medidos
- Conclusion clara: viable, viable con ajustes, o no viable con justificacion

---

*Este documento se actualiza con los resultados reales durante la Semana 2 del proyecto.*
