# Configuración básica

> *Configura o teu ornitóptero para o primeiro voo.*

## Lista de verificación previa ao voo

Antes de nada:

- [ ] O controlador de voo parpadeou con OrniFlight
- [ ] Receptor conectado ao transmisor
- [ ] Servos conectados para corrixir as saídas PWM
- [ ] Batería conectada (as aseguradas!)

## Configuración do receptor

### CRSF (Recomendado)

1. **Ports tab**: Set UART (e.g. UART1) to "Serial RX"
2. **Pestaña Configuración**: Modo receptor = "Receptor baseado en serie", Provedor = "CRSF"
3. Ciclo de alimentación, verifique que as entradas da canle se movan na pestana Receptor

### SBUS / Outros

Mesmo proceso —, seleccione o protocolo apropiado na pestana Configuración.

## Mapeo de servos

Na pestana **Servos**:

| Servo | Función | Taxa predeterminada |
|-------|-----------|--------------|
| Servo 0 | Á esquerda | 250 Hz |
| Servo 1 | Á dereita | 250 Hz |
| Servo 2 | Cresta/Temón | 50 Hz |

Axusta mínimo/máx./medio para que coincida co rango do teu servo. Proba con "Anular" para verificar a dirección.

## Selección do modo de voo

Na pestana **Modos**:

1. **ARM**: Asignar a un interruptor (seguridade!)
2. **ORNITHOPTER INDEPENDENT** ou **ORNITHOPTER GLIDE**: escolle o teu modo de voo principal
3. **ORNITHOPTER PROFILE**: asignación de — opcional para o cambio de perfil durante o voo

## ONDAS Primeira afinación

Vaia á **subpestaña avanzada → ONDAS**:

1. **Cadence Gain**: comeza a 50 (mediados). Este é o parámetro máis importante.
2. **Ferocity D Gain**: comeza ás 30. Esta é a túa estabilización principal.
3. **Ferocity P Gain**: comeza a partir de 20 para rollo / cabeceo, 0 para guiñada.
4. **Balance Ganancia**: 0 (centrado).

Conecte unha batería, **fixe firmemente o ornitóptero** e ARM. Observe o movemento do servo — debe ser suave e sinusoidal.

## First Flight

1. Comeza cun lanzamento suave ao vento
2. Usa o modo GLIDE para unha sensación natural de elevación
3. Use o modo INDEPENDENT cando quere controlar a frecuencia directa
4. Aterra, axusta ONDAS, repite

---

*Seguinte: [ONDAS Guía de afinación](ondas_tuning.html) →*