# Registro de caja negra

Blackbox registra datos de vuelo para análisis, ajuste y depuración posteriores al vuelo. OrniFlight admite el registro en el chip flash integrado o en un dispositivo OpenLog externo.

## Qué se registra

- **Gyro** — velocidad angular de 3 ejes sin procesar y filtrada
- **Acelerómetro** — aceleración de 3 ejes
- **PID Salida** — Contribuciones P, I, D, F por eje
- **ONDAS** — Cadence, Ferocity P/D y otros parámetros específicos de aleteo
- **Comandos RC** — posiciones del stick después de tarifas/expo
- **Salida de servo** — salida final a cada canal de servo
- **Batería** voltaje y corriente — por iteración
- **GPS** — posición, velocidad, altitud (cuando esté disponible)

## Configuración

### Flash integrado (OMNIBUSF4)

El OMNIBUSF4 incluye flash integrado de 16 MB para registro de Blackbox. Habilitar en el Configurador:

1. Pestaña **Blackbox** → Establezca `Blackbox logging device` en `Onboard flash`
2. Establezca la tasa de registro (recomendado: `1/N` con N=2-4 para objetivos F4)
3. Asigne un interruptor para iniciar/detener el registro

### Externo OpenLog

Conecte OpenLog a un pin UART TX libre:

1. Pestaña **Puertos** → Configure el UART en `Blackbox logging` a 115200 baudios.
2. Conecte OpenLog: FC TX → OpenLog RX, más 5V/GND

## Herramientas de análisis

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — visor de registros basado en web
- `blackbox_decode` — convierte a CSV para análisis personalizados

## ONDAS-Específico

Blackbox es esencial para ajustar los parámetros del ONDAS. Los datos registrados de ONDAS incluyen:
- sincronización de la ventana de modulación `ondas_cadence_phase` —
- componentes de empuje asimétricos `ondas_ferocity_p` / `ondas_ferocity_d` —
- `ondas_balance` — equilibrio ala izquierda/derecha
- Salida por servo en cada iteración

Esto permite un análisis preciso de la mecánica de aleteo y las correcciones de asimetría del ala.