#Controis

OrniFlight usa mapeo estándar RC con extensións específicas de ornitópteros.

## Mapeo de Stick

| Palo | Eixo | Efecto primario |
|-------|-------|----------------|
| Acelerador (esquerda, vertical) | Acelerador | Amplitude / empuxe do aleteo |
| Guiñada (esquerda, horizontal) | Guiña | Diferencial de empuxe alar para virar |
| Paso (Dereita, vertical) | Pitch | Inclinación cara adiante/atrás |
| Rodar (Dereita, horizontal) | Rolo | Banca esquerda/dereita |

## Modos de voo

| Modo | Comportamento de vara |
|------|----------------|
| **ACRO** | Os palos controlan a taxa angular — sen nivel automático |
| **ANGLE** | Os palos controlan o ángulo — autonivel cando se solta |
| **HORIZON** | ANGLE preto do centro, ACRO en plena desviación |

ACRO recoméndase para pilotos experimentados. ANGLE é bo para os primeiros voos e as altas térmicas.

## Controis específicos de ornitópteros

### Modo INDEPENDENT

Cando o modo INDEPENDENT está activo, cada servo de á responde de forma independente:
- **Palo esquerdo** → servos á esquerda
- **Palo dereito** → servos á dereita
- Permite o aleteo asimétrico para manobras agresivas

### Modo GLIDE

O modo GLIDE bloquea as dúas ás en posición horizontal. O ornitóptero convértese nun planeador:
- **O acelerador** non ten efecto na posición das ás
- **Pitch/Roll/Yaw** aínda inflúe nas superficies de control de cola (se está equipado)

### Cambio de perfil

O cambio de perfil durante o voo a través da canle AUX permite cambiar os parámetros PID/ONDAS durante o voo:
- **Perfil 1**: configuración estándar de cruceiro
- **Perfil 2**: configuración de alta axilidade
- **Perfil 3**: axustes de eficiencia/deslizamento

## Tarifas

Configure as tarifas na pestana **PID Tuning**. Para ornitópteros, comeza con taxas conservadoras — dinámica de aleteo amplifica as entradas de control:
- Tarifa RC: 0,80–1,00
- Supertaxa: 0,60–0,70
- Expo: 0,20–0,40