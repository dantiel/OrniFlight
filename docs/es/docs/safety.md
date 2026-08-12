# Seguridad

## Lista de verificación previa al vuelo

1. **Alas**: Asegúrese de que las alas estén montadas de forma segura y que el varillaje esté intacto.
2. **Batería**: Totalmente cargada, correctamente asegurada, recuento de celdas correcto
3. **Controles**: Verifique las respuestas del joystick en la pestaña del receptor del Configurador
4. **A prueba de fallos**: prueba en banco antes del vuelo (consulte [A prueba de fallos](failsafe.html))
5. **Arm Switch**: Configure y pruebe —, nunca confíe únicamente en el armado mediante palanca
6. **Área de lanzamiento**: libre de personas, obstáculos y obstrucciones aéreas

## Seguridad del brazo

OrniFlight utiliza múltiples dispositivos de seguridad antes de armar:

- **Acelerador bajo**: el acelerador debe estar al mínimo
- **Nivel**: la embarcación debe estar razonablemente nivelada
- **RX Signal**: Se requiere una señal de receptor válida
- **CPU Load**: El sistema no debe estar sobrecargado
- **Calibración**: el acelerómetro y el giroscopio deben estar calibrados

## Seguridad en vuelo

- **Vuela dentro del campo visual**
- Mantener una distancia segura con personas y animales.
- Monitorear el voltaje de la batería — aterrizar antes del umbral de advertencia
- En FPV: vuela siempre con un observador.
- Viento: los ornitópteros pueden ser sensibles al viento — conoce tus límites

## Procedimientos de emergencia

| Situación | Acción |
|-----------|----------------|
| Pérdida de orientación | Cambiar al modo INDEPENDENT, palancas centrales |
| Pérdida de señal | Failsafe aterrizará automáticamente (si se configura el procedimiento LAND) |
| Daños en las alas | Desarmar inmediatamente — alas detener |
| Golpe de pájaro | Desarmar, evaluar daños antes de rearmar |
| Batería baja | Los ornitópteros aterrizan inmediatamente — no tienen autorrotación |

## Riesgos específicos de los ornitópteros

- **Peligro de pellizco**: el aleteo de las alas puede causar lesiones — mantén las manos alejadas cuando estés armado
- **Falla del varillaje**: antes del vuelo verifique todas las varillas de empuje y las rótulas
- **Resonance**: Ciertas frecuencias de aleteo pueden excitar resonancias del fuselaje — sintoniza ONDAS barrido para evitar
- **Bloqueo de planeo**: Si los servos del ala fallan en una posición no neutral, el aterrizaje controlado es imposible — prueba las posiciones de seguridad de los servos