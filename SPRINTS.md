# CRONOGRAMA DE SPRINTS — HydroSense

Metodologia: Agile / Scrum adaptado para proyecto academico.
Duracion total: 8 semanas. Sprints de 1 semana. Releases cada 2 semanas.

---

## Vista general

| Release | Semanas | Foco principal | Entregable |
|---------|---------|----------------|------------|
| Release 1 | 1 y 2 | Investigacion y spike tecnico | Documento de spike + diseno validado |
| Release 2 | 3 y 4 | Hardware y firmware base | ESP32 con sensores y control de bomba funcionando |
| Release 3 | 5 y 6 | Integracion nube y dashboard | Sistema completo funcional de extremo a extremo |
| Release 4 | 7 y 8 | Pulido, pruebas y presentacion | Producto final y documentacion |

---

## Release 1 — Fundamentos y viabilidad (Semanas 1 y 2)

**Objetivo:** Validar la viabilidad tecnica del proyecto y tomar decisiones de arquitectura con evidencia experimental.

### Sprint 1 (Semana 1) — Investigacion y diseno

| Tarea | Tipo | Estado |
|-------|------|--------|
| Definir alcance del MVP con el equipo | Planning | Pendiente |
| Investigar plataformas IoT: Firebase vs ThingSpeak vs MQTT broker propio | Research | Pendiente |
| Seleccionar sensor de humedad: resistivo vs capacitivo | Research | Pendiente |
| Disenar arquitectura del sistema (diagrama de bloques) | Design | Pendiente |
| Crear repositorio en GitHub con estructura de carpetas | Setup | Pendiente |
| Redactar README inicial | Docs | Pendiente |
| Definir convenciones de codigo y politica de branching | Setup | Pendiente |

**Entregable:** Repositorio creado, arquitectura documentada y decisiones tecnicas registradas.

---

### Sprint 2 (Semana 2) — Spike tecnico

| Tarea | Tipo | Estado |
|-------|------|--------|
| Adquirir los componentes de hardware | Logistica | Pendiente |
| [SPIKE-01] Probar lectura del sensor con ESP32 (minimo 50 muestras por condicion) | Spike | Pendiente |
| [SPIKE-01] Probar conexion MQTT a broker en la nube | Spike | Pendiente |
| Documentar resultados del spike con tablas y conclusiones | Docs | Pendiente |
| Definir umbrales de humedad: SECO, NORMAL, SATURADO | Research | Pendiente |
| Crear diagrama de conexiones electricas (Fritzing o similar) | Design | Pendiente |
| Configurar entorno PlatformIO en los equipos del equipo | Setup | Pendiente |

**Entregable:** Reporte del spike con conclusiones. Diagrama electrico. Entorno de desarrollo listo.

**Criterio de exito del Release 1:**
- Spike completado y documentado en el README
- Viabilidad tecnica confirmada
- Arquitectura final acordada por el equipo
- Backlog con MVP definido visible en el tablero de GitHub Projects

---

## Release 2 — Hardware y firmware base (Semanas 3 y 4)

**Objetivo:** Tener el ESP32 leyendo sensores, evaluando umbrales y controlando la bomba sin dependencia de la nube.

### Sprint 3 (Semana 3) — Firmware de sensores

| Tarea | Tipo | Estado |
|-------|------|--------|
| [FEAT-01] Implementar modulo de lectura de sensores (sensors.cpp) | Feature | Pendiente |
| Calibrar sensores con valores de referencia conocidos | Research | Pendiente |
| Implementar funcion de mapeo ADC a porcentaje | Feature | Pendiente |
| Implementar salida Serial para depuracion | Feature | Pendiente |
| Montar circuito en protoboard: sensores + ESP32 | Hardware | Pendiente |
| Escribir pruebas unitarias del modulo de sensores | Test | Pendiente |

**Entregable:** ESP32 leyendo dos sensores y mostrando porcentaje de humedad por puerto Serial.

---

### Sprint 4 (Semana 4) — Logica de control y actuador

| Tarea | Tipo | Estado |
|-------|------|--------|
| [FEAT-02] Implementar maquina de estados: SECO / NORMAL / SATURADO | Feature | Pendiente |
| [FEAT-03] Implementar control del rele y la bomba | Feature | Pendiente |
| Implementar temporizador de riego maximo (anti-inundacion) | Feature | Pendiente |
| Completar circuito fisico: rele + bomba + fuente de alimentacion | Hardware | Pendiente |
| Prueba integrada: sensor detecta seco, bomba se activa, se apaga al humedecer | Test | Pendiente |
| Documentar diagrama electrico final | Docs | Pendiente |

**Entregable:** Sistema fisico funcional en modo local. La bomba se activa y desactiva automaticamente segun los umbrales.

**Criterio de exito del Release 2:**
- Lectura estable de dos sensores en condiciones reales
- Bomba controlada correctamente por la logica de umbrales
- Prueba de riego automatico documentada con fotos o video

---

## Release 3 — Integracion nube y dashboard (Semanas 5 y 6)

**Objetivo:** Conectar el sistema a la nube y proveer al usuario visibilidad y control remoto en tiempo real.

### Sprint 5 (Semana 5) — Conectividad y backend

| Tarea | Tipo | Estado |
|-------|------|--------|
| [FEAT-04] Implementar modulo WiFi con reconexion automatica | Feature | Pendiente |
| [FEAT-04] Implementar cliente MQTT con PubSubClient | Feature | Pendiente |
| Configurar Firebase Realtime Database y reglas de seguridad | Setup | Pendiente |
| Definir estructura de datos en Firebase | Design | Pendiente |
| Implementar publicacion de lecturas cada 5 minutos | Feature | Pendiente |
| [FEAT-05] Configurar Firebase Cloud Functions para logica de alertas | Feature | Pendiente |
| [FEAT-05] Implementar envio de notificaciones via FCM | Feature | Pendiente |

**Entregable:** ESP32 publicando datos a Firebase. Notificaciones push funcionando.

---

### Sprint 6 (Semana 6) — Dashboard web

| Tarea | Tipo | Estado |
|-------|------|--------|
| [FEAT-06] Crear proyecto React con estructura de carpetas | Setup | Pendiente |
| [FEAT-06] Implementar vista de estado en tiempo real | Feature | Pendiente |
| [FEAT-06] Implementar grafica de historial (ultimas 24 h) | Feature | Pendiente |
| [FEAT-06] Implementar boton de riego manual | Feature | Pendiente |
| Integrar dashboard con Firebase (lectura en tiempo real) | Feature | Pendiente |
| Prueba de integracion de extremo a extremo | Test | Pendiente |

**Entregable:** Sistema completo funcionando de extremo a extremo.

**Criterio de exito del Release 3:**
- Datos visibles en el dashboard en menos de 10 s desde la lectura
- Notificacion push recibida al bajar la humedad
- Bomba controlable desde el dashboard de forma remota

---

## Release 4 — Pulido y entrega final (Semanas 7 y 8)

**Objetivo:** Corregir errores, estabilizar el sistema, completar la documentacion y preparar la presentacion.

### Sprint 7 (Semana 7) — Pruebas y correccion de errores

| Tarea | Tipo | Estado |
|-------|------|--------|
| Prueba de funcionamiento continuo durante 48 horas | Test | Pendiente |
| Documentar y corregir todos los bugs encontrados | Bug | Pendiente |
| Optimizar consumo de memoria del firmware | Improvement | Pendiente |
| Revisar y mejorar la interfaz del dashboard | Improvement | Pendiente |
| Prueba de reconexion WiFi (simular corte de red) | Test | Pendiente |
| Revisar reglas de seguridad en Firebase | Security | Pendiente |
| Completar la documentacion tecnica en la carpeta /docs | Docs | Pendiente |

---

### Sprint 8 (Semana 8) — Documentacion final y presentacion

| Tarea | Tipo | Estado |
|-------|------|--------|
| Actualizar README con resultados y fotos del sistema final | Docs | Pendiente |
| Grabar video demo del sistema en funcionamiento | Demo | Pendiente |
| Preparar presentacion del proyecto (diapositivas) | Presentacion | Pendiente |
| Escribir seccion de lecciones aprendidas | Docs | Pendiente |
| Crear release v1.0.0 en GitHub con tag | Release | Pendiente |
| Ensayo de la presentacion final | Presentacion | Pendiente |

**Criterio de exito del Release 4:**
- Sistema estable sin intervencion durante 48 horas
- README completo con toda la documentacion del proyecto
- Video demo publicado y enlazado en el README
- Release v1.0.0 etiquetado en GitHub

---

## Convencion de branches

```
main          <- codigo estable, solo se actualiza por Pull Request aprobado
develop       <- integracion continua del equipo
feature/XXX   <- una rama por feature o issue
spike/XXX     <- investigacion tecnica
fix/XXX       <- correccion de bugs
```

Regla: ningun commit directo a main. Todo cambio pasa por Pull Request con al menos una revision de otro miembro del equipo.

---

*Actualizar el estado de cada tarea al final de cada sprint.*
