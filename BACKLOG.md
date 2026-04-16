# BACKLOG — HydroSense

Listado de features organizado por prioridad. Cada item corresponde a un Issue en GitHub.

---

## MVP — Must Have

Estas features son indispensables para una version funcional del sistema.

---

### [FEAT-01] Lectura de sensores de humedad del suelo

**Tipo:** feature | **Prioridad:** critica | **Sprint:** Release 2

**Descripcion:**
Implementar la lectura del sensor de humedad conectado al ADC del ESP32. El sistema toma multiples muestras, las promedia y mapea el valor ADC a un porcentaje de humedad (0–100 %).

**Criterios de aceptacion:**
- [ ] Lectura cada 5 minutos (intervalo configurable)
- [ ] Promedio de 20 muestras para reducir ruido del ADC
- [ ] Valor mapeado a porcentaje de humedad
- [ ] Soporte para dos sensores simultaneos
- [ ] Salida por Serial para depuracion

**Notas tecnicas:**
- Usar GPIO34 y GPIO35 (ADC1). No usar pines ADC2 con WiFi activo.
- Rango ADC esperado: 900 (saturado) a 3.400 (seco).

---

### [FEAT-02] Logica de decision con umbrales configurables

**Tipo:** feature | **Prioridad:** critica | **Sprint:** Release 2

**Descripcion:**
Evaluar la humedad leida contra umbrales definidos y determinar la accion correspondiente: Ninguna accion, alerta al usuario o activacion de la bomba.

**Criterios de aceptacion:**
- [ ] Umbral bajo configurable (default: 30 % — suelo seco)
- [ ] Umbral alto configurable (default: 75 % — suelo saturado)
- [ ] Tres estados de salida: SECO, NORMAL, SATURADO
- [ ] Umbrales modificables desde la nube sin re-flashear el firmware

---

### [FEAT-03] Activacion automatica de la bomba de agua

**Tipo:** feature | **Prioridad:** critica | **Sprint:** Release 2

**Descripcion:**
Controlar el rele que activa la bomba cuando la humedad cae por debajo del umbral bajo. Incluye tiempo maximo de riego para prevenir inundacion.

**Criterios de aceptacion:**
- [ ] Activar bomba cuando humedad < umbral bajo
- [ ] Tiempo maximo de riego: 30 s (configurable)
- [ ] Apagar bomba cuando humedad supera el umbral de corte
- [ ] Registrar el evento de riego en la nube
- [ ] Modo manual: activar o desactivar bomba desde el dashboard

**Notas tecnicas:**
- Pin de control: GPIO26 (salida digital).
- Verificar si el modulo de rele es activo en LOW o en HIGH.

---

### [FEAT-04] Envio de datos a la nube via MQTT

**Tipo:** feature | **Prioridad:** critica | **Sprint:** Release 3

**Descripcion:**
Transmitir las lecturas de los sensores y los eventos del sistema a Firebase Realtime Database usando MQTT.

**Criterios de aceptacion:**
- [ ] Publicar lectura cada 5 minutos en formato JSON
- [ ] Reconexion automatica con backoff exponencial en caso de perdida de WiFi
- [ ] Estructura de datos: `/plantas/{id}/lecturas/{timestamp}`
- [ ] QoS 1 para eventos criticos (riego activado)
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

### [FEAT-05] Notificacion push al usuario

**Tipo:** feature | **Prioridad:** alta | **Sprint:** Release 3

**Descripcion:**
Enviar notificacion push al usuario cuando la humedad baja del umbral o cuando se activa el riego automatico, usando Firebase Cloud Messaging (FCM).

**Criterios de aceptacion:**
- [ ] Notificacion al detectar humedad < umbral bajo
- [ ] Notificacion al activar el riego automatico
- [ ] Limite de una notificacion por hora por planta (anti-spam)
- [ ] La notificacion incluye nombre de la planta y porcentaje actual

---

### [FEAT-06] Dashboard web de monitoreo

**Tipo:** feature | **Prioridad:** alta | **Sprint:** Release 3

**Descripcion:**
Interfaz web que muestra el estado actual de las plantas, el porcentaje de humedad en tiempo real y permite controlar la bomba de forma manual.

**Criterios de aceptacion:**
- [ ] Mostrar humedad actual de cada sensor en tiempo real
- [ ] Indicador visual de estado: Normal / Alerta / Seco
- [ ] Boton de activacion manual de la bomba
- [ ] Historial de las ultimas 24 horas en grafica de lineas
- [ ] Interfaz responsive (usable desde movil)

---

### [SPIKE-01] Validacion tecnica: sensores y conectividad WiFi

**Tipo:** spike | **Prioridad:** critica | **Sprint:** Release 1

**Descripcion:**
Validar experimentalmente si el ADC del ESP32 entrega lecturas estables con los sensores YL-69, y si la conexion MQTT a Firebase es confiable en una red domestica. Tarea de mayor incertidumbre tecnica del proyecto.

**Criterios de aceptacion:**
- [ ] Documento con resultados de pruebas (minimo 50 muestras por condicion)
- [ ] Umbrales de calibracion definidos y justificados
- [ ] Tasa de entrega MQTT > 95 %
- [ ] Decision documentada: sensor resistivo o capacitivo

Ver resultado en la seccion [Reporte del spike](./README.md#reporte-del-spike) del README.

---

## Nice to Have

Estas features agregan valor pero no son requeridas para el MVP.

---

### [FEAT-07] Aplicacion movil

**Tipo:** feature | **Prioridad:** media | **Sprint:** Post-MVP

**Descripcion:**
Version movil del dashboard con notificaciones nativas, control de la bomba y visualizacion de historicos.

---

### [FEAT-08] Historicos y graficas avanzadas

**Tipo:** feature | **Prioridad:** media | **Sprint:** Post-MVP

**Descripcion:**
Almacenar y visualizar el historial completo de humedad con graficas de tendencia, promedios diarios y comparacion entre plantas.

---

### [FEAT-09] Prediccion de riego

**Tipo:** feature | **Prioridad:** baja | **Sprint:** Post-MVP

**Descripcion:**
Usar datos historicos para predecir cuando sera necesario el proximo riego, considerando patrones de consumo y condiciones ambientales.

---

### [FEAT-10] Integracion con asistentes de voz

**Tipo:** feature | **Prioridad:** baja | **Sprint:** Post-MVP

**Descripcion:**
Permitir comandos de voz mediante Alexa o Google Home para consultar el estado de las plantas o activar el riego.

---

### [FEAT-11] Modo de bajo consumo con bateria

**Tipo:** feature | **Prioridad:** baja | **Sprint:** Post-MVP

**Descripcion:**
Implementar deep sleep agresivo y soporte para panel solar con bateria LiPo, para instalaciones sin acceso a corriente.

---

## Bugs tecnicos conocidos

### [BUG-01] ADC2 no disponible en modo WiFi

**Tipo:** bug | **Prioridad:** alta

**Descripcion:** Los pines ADC2 del ESP32 (GPIO0, 2, 4, 12–15, 25–27) son incompatibles con WiFi activo.

**Solucion:** Usar unicamente pines ADC1 (GPIO32–GPIO39) para los sensores.

---

### [BUG-02] No linealidad del ADC en los extremos del rango

**Tipo:** bug | **Prioridad:** media

**Descripcion:** El ADC del ESP32 es no lineal cerca de 0 V y 3.3 V, lo que puede distorsionar lecturas en suelos muy secos o muy saturados.

**Solucion:** Aplicar curva de calibracion o usar la funcion `esp_adc_cal_characterize()` de ESP-IDF.

---

*Actualizar el estado de cada item a medida que avanza el proyecto.*
