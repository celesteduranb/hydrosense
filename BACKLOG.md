# BACKLOG — HydroSense

Listado de features organizado por prioridad. Cada item corresponde a un Issue en GitHub.

---

## MVP — Must Have

Estas features son indispensables para una versión funcional del sistema.

---

### [FEAT-01] Lectura de sensores de humedad del suelo

**Tipo:** feature | **Prioridad:** crítica | **Sprint:** Release 2

**Descripcion:**
Implementar la lectura del sensor de humedad conectado al ADC del ESP32. El sistema toma múltiples muestras, las promedia y mapea el valor ADC a un porcentaje de humedad (0–100 %).

**Criterios de aceptación:**
- [ ] Lectura cada 5 minutos (intervalo configurable)
- [ ] Promedio de 20 muestras para reducir ruido del ADC
- [ ] Valor mapeado a porcentaje de humedad
- [ ] Soporte para dos sensores simultáneos
- [ ] Salida por Serial para depuración

**Notas técnicas:**
- Usar GPIO34 y GPIO35 (ADC1). No usar pines ADC2 con WiFi activo.
- Rango ADC esperado: 900 (saturado) a 3.400 (seco).

---

### [FEAT-02] Lógica de decisión con umbrales configurables

**Tipo:** feature | **Prioridad:** critica | **Sprint:** Release 2

**Descripción:**
Evaluar la humedad leida contra umbrales definidos y determinar la accion correspondiente: Ninguna acción, alerta al usuario o activación de la bomba.

**Criterios de aceptación:**
- [ ] Umbral bajo configurable (default: 30 % — suelo seco)
- [ ] Umbral alto configurable (default: 75 % — suelo saturado)
- [ ] Tres estados de salida: SECO, NORMAL, SATURADO
- [ ] Umbrales modificables desde la nube sin re-flashear el firmware

---

### [FEAT-03] Activación automática de la bomba de agua

**Tipo:** feature | **Prioridad:** crítica | **Sprint:** Release 2

**Descripción:**
Controlar el rele que activa la bomba cuando la humedad cae por debajo del umbral bajo. Incluye tiempo máximo de riego para prevenir inundación.

**Criterios de aceptacion:**
- [ ] Activar bomba cuando humedad < umbral bajo
- [ ] Tiempo máximo de riego: 30 s (configurable)
- [ ] Apagar bomba cuando humedad supera el umbral de corte
- [ ] Registrar el evento de riego en la nube
- [ ] Modo manual: activar o desactivar bomba desde el dashboard

**Notas técnicas:**
- Pin de control: GPIO26 (salida digital).
- Verificar si el modulo de rele es activo en LOW o en HIGH.

---

### [FEAT-04] Envío de datos a la nube via MQTT

**Tipo:** feature | **Prioridad:** crítica | **Sprint:** Release 3

**Descripción:**
Transmitir las lecturas de los sensores y los eventos del sistema a Firebase Realtime Database usando MQTT.

**Criterios de aceptación:**
- [ ] Publicar lectura cada 5 minutos en formato JSON
- [ ] Reconexión automática con backoff exponencial en caso de perdida de WiFi
- [ ] Estructura de datos: `/plantas/{id}/lecturas/{timestamp}`
- [ ] QoS 1 para eventos críticos (riego activado)
- [ ] LED indicador del estado de conexion

**Ejemplo de payload:**
```json
{
  "planta_id": "maceta_01",
  "humedad_pct": 27.5,
  "estado": "SECO",
  "bomba_activa": true,
  "timestamp": 1712345678
}
```

---

### [FEAT-05] Notificación push al usuario

**Tipo:** feature | **Prioridad:** alta | **Sprint:** Release 3

**Descripcion:**
Enviar notificación push al usuario cuando la humedad baja del umbral o cuando se activa el riego automático, usando Firebase Cloud Messaging (FCM).

**Criterios de aceptación:**
- [ ] Notificación al detectar humedad < umbral bajo
- [ ] Notificación al activar el riego automatico
- [ ] Límite de una notificación por hora por planta (anti-spam)
- [ ] La notificación incluye nombre de la planta y porcentaje actual

---

### [FEAT-06] Dashboard web de monitoreo

**Tipo:** feature | **Prioridad:** alta | **Sprint:** Release 3

**Descripcion:**
Interfaz web que muestra el estado actual de las plantas, el porcentaje de humedad en tiempo real y permite controlar la bomba de forma manual.

**Criterios de aceptación:**
- [ ] Mostrar humedad actual de cada sensor en tiempo real
- [ ] Indicador visual de estado: Normal / Alerta / Seco
- [ ] Botón de activación manual de la bomba
- [ ] Historial de las últimas 24 horas en gráfica de lineas
- [ ] Interfaz responsive (usable desde móvil)

---

### [SPIKE-01] Validación técnica: sensores y conectividad WiFi

**Tipo:** spike | **Prioridad:** crítica | **Sprint:** Release 1

**Descripcion:**
Validar experimentalmente si el ADC del ESP32 entrega lecturas estables con los sensores YL-69, y si la conexión MQTT a Firebase es confiable en una red domestica. Tarea de mayor incertidumbre técnica del proyecto.

**Criterios de aceptación:**
- [ ] Documento con resultados de pruebas (mínimo 50 muestras por condición)
- [ ] Umbrales de calibración definidos y justificados
- [ ] Tasa de entrega MQTT > 95 %
- [ ] Decisión documentada: sensor resistivo o capacitivo

Ver resultado en la seccion [Reporte del spike](./README.md#reporte-del-spike) del README.

---

## Nice to Have

Estas features agregan valor pero no son requeridas para el MVP.

---

### [FEAT-07] Aplicación móvil

**Tipo:** feature | **Prioridad:** media | **Sprint:** Post-MVP

**Descripcion:**
Versión móvil del dashboard con notificaciones nativas, control de la bomba y visualización de históricos.

---

### [FEAT-08] Históricos y gráficas avanzadas

**Tipo:** feature | **Prioridad:** media | **Sprint:** Post-MVP

**Descripción:**
Almacenar y visualizar el historial completo de humedad con graficas de tendencia, promedios diarios y comparacion entre plantas.

---

### [FEAT-09] Predicción de riego

**Tipo:** feature | **Prioridad:** baja | **Sprint:** Post-MVP

**Descripción:**
Usar datos historicos para predecir cuando sera necesario el próximo riego, considerando patrones de consumo y condiciones ambientales.

---

### [FEAT-10] Integración con asistentes de voz

**Tipo:** feature | **Prioridad:** baja | **Sprint:** Post-MVP

**Descripción:**
Permitir comandos de voz mediante Alexa o Google Home para consultar el estado de las plantas o activar el riego.

---

### [FEAT-11] Modo de bajo consumo con batería

**Tipo:** feature | **Prioridad:** baja | **Sprint:** Post-MVP

**Descripción:**
Implementar deep sleep agresivo y soporte para panel solar con bateria LiPo, para instalaciones sin acceso a corriente.

---

## Bugs técnicos conocidos

### [BUG-01] ADC2 no disponible en modo WiFi

**Tipo:** bug | **Prioridad:** alta

**Descripción:** Los pines ADC2 del ESP32 (GPIO0, 2, 4, 12–15, 25–27) son incompatibles con WiFi activo.

**Solución:** Usar unicamente pines ADC1 (GPIO32–GPIO39) para los sensores.

---

### [BUG-02] No linealidad del ADC en los extremos del rango

**Tipo:** bug | **Prioridad:** media

**Descripcion:** El ADC del ESP32 es no lineal cerca de 0 V y 3.3 V, lo que puede distorsionar lecturas en suelos muy secos o muy saturados.

**Solucion:** Aplicar curva de calibracion o usar la funcion `esp_adc_cal_characterize()` de ESP-IDF.

---

*Actualizar el estado de cada item a medida que avanza el proyecto.*
