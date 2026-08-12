# ONDAS Guia de ajuste

> *O companheiro prático da Teoria ONDAS — sobre como ajustar cada parâmetro pela sensação.*

## Ordem de ajuste

Os parâmetros ONDAS são interdependentes. Sintonize-os nesta sequência:

```
1. Cadence    →  timing
2. Ferocity D →  primary stabilization
3. Ferocity P →  response crispness
4. Balance    →  upstroke/downstroke bias
5. Warp       →  modulation width
6. Anchor     →  dry/wet mix
7. Resonance  →  cycle-to-cycle memory
8. Phase 2    →  advanced (prescience, espelho, saudade, SSFF)
```

## Passo a passo

### 1. Cadence — Encontre sua janela de fase

**Objetivo**: Coloque a modulação onde sua asa tem mais força.

**Método**: 
- Comece aos 50
- Aumentar para 70 — a resposta do roll fica mais fraca?
- Diminuir para 30 — a resposta do roll fica mais forte?
- O ponto "mais forte" é onde o golpe de força da sua asa atinge o pico

**Sinais de muito alto**: resposta mole, a nave parece "atrasada"
**Sinais de muito baixo**: Resposta brusca, ultrapassagem na rolagem

### 2. Ferocity D — Estabeleça a Arte

**Objetivo**: Estabilização primária sem oscilação.

**Método**:
- Comece às 20
- Hover ou vôo constante para frente
- Aumente até sentir o artesanato "endurecer"
- Afaste-se 5 pontos de onde você percebe a oscilação pela primeira vez

**Sinais de muito alto**: Vibração fina, zumbido semelhante ao de um motor nos servos
**Sinais de muito baixo**: a embarcação flutua, parece solta

### 3. Ferocity P — Crocância

**Objetivo**: Responsivo, mas não nervoso.

**Método**:
- Comece às 15
- Bata no bastão — a nave morde imediatamente?
- Aumente até que a resposta do stick seja nítida
- Recue se você perceber um overshoot

**Sinais de muito alto**: Toque após a entrada do stick, retorno
**Sinais de muito baixo**: Resposta mole e atrasada

### 4. Balance — Ajuste de assimetria

**Objetivo**: Autoridade igual em ambas as direções.

**Método**:
- Voe reto e nivelado
- Role para a esquerda, observe a velocidade de resposta
- Role para a direita, observe a velocidade de resposta
- Ajuste o equilíbrio para equalizá-los

###5–7. Warp, Anchor, Resonance

Parâmetros de ajuste fino. Ajuste somente depois que 1-4 estiverem sólidos.

| Parâmetro | Iniciar | Ajustar quando |
|-------|-------|-------------|
| Warp | 50 | A modulação parece muito espalhada ou muito pontiaguda |
| Anchor | 70 | Quer mais/menos PID cru misturado |
| Resonance | 30 | Pairar instável ou voar para frente parece estranho |

### 8. Phase 2 — Avançado

| Parâmetro | Efeito |
|-------|--------|
| Prescience | Avanço de tempo — maior = modulação leva mais fase |
| Espelho | Acoplamento diferencial — rolo mais apertado, pode reduzir a eficiência |
| Saudade | Memória de curso — mais suave, mas menos responsiva |
| SSFF | Injeção direta de giro→wave — começa em 10 |

---

*O objetivo é uma nave que voe como se quisesse estar no ar. Se você estiver lutando contra isso, recue e sintonize novamente de Cadence para cima.*