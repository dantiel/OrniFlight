# Controles

OrniFlight utiliza el mapeo de palo estándar RC con extensiones específicas para ornitópteros.

## Mapeo de palos

| Palo | Eje | Efecto primario |
|-------|------|-----------------------|
| Acelerador (izquierda, vertical) | Acelerador | Amplitud/empuje del aleteo |
| Guiñada (izquierda, horizontal) | Guiñada | Empuje de ala diferencial para giro |
| Paso (Derecha, vertical) | Lanzamiento | Inclinación hacia adelante/atrás |
| Rollo (derecha, horizontal) | Rollo | Banca izquierda/derecha |

## Modos de vuelo

| Modo | Comportamiento del palo |
|------|---------------|
| **ACRO** | Los palos controlan la velocidad angular — sin nivel automático |
| **ANGLE** | Ángulo de control de palos — nivel automático cuando se suelta |
| **HORIZON** | ANGLE cerca del centro, ACRO en plena desviación |

Se recomienda ACRO para pilotos experimentados. ANGLE es bueno para primeros vuelos y vuelos térmicos.

## Controles específicos de ornitópteros

### Modo INDEPENDENT

Cuando el modo INDEPENDENT está activo, cada servo de ala responde de forma independiente:
- **Stick izquierdo** → servos del ala izquierda
- **Stick derecho** → servos del ala derecha
- Permite aleteo asimétrico para maniobras agresivas.

### Modo GLIDE

El modo GLIDE bloquea ambas alas en posición horizontal. El ornitóptero se convierte en planeador:
- **Acelerador** no tiene efecto en la posición del ala
- **Inclinación/Balanceo/Guía** aún influye en las superficies de control de cola (si está equipado)

### Cambio de perfil

El cambio de perfil en vuelo a través del canal AUX permite cambiar los parámetros PID/ONDAS en pleno vuelo:
- **Perfil 1**: configuración de crucero estándar
- **Perfil 2**: Configuración de alta agilidad
- **Perfil 3**: Configuración de eficiencia/deslizamiento

## Tarifas

Configura tarifas en la pestaña **PID Tuning**. Para los ornitópteros, comience con tasas conservadoras. La dinámica de aleteo — amplifica las entradas de control:
- RC Tarifa: 0.80–1.00
- Súper Tarifa: 0.60–0.70
- Expo: 0.20–0.40