# ONDAS — Estabilització adaptativa dinàmica normalitzada oscil·lant

## El principi bàsic

Un avió d'ala fixa o convencional genera forces de control **contínuament** — una deflexió de la superfície de control o RPM canvi produeix un moment en estat estacionari. Un ornitòpter no. Cada gram d'empenta, cada Newton de parell, està **limitat per fase** dins del cicle de batec d'ala. El mateix impuls de força aplicat en diferents punts de la carrera produeix resultats fonamentalment diferents.

ONDAS reconeix aquesta realitat i modula l'esforç d'estabilització de manera sincrònica amb el cicle de bateig.

---

## Cadence — El cervell del temps

Cadence és el filtre ONDAS més crític perquè determina **quan** es produeix la correcció dins de cada batec d'ala.

| Fase d'ictus | Efecte de l'aplicació de la força |
|---|---|
| Centre de baixada | Elevació màxima, autoritat de rodatge |
| Final de baixada (frenada) | Moment de guiñada d'arrossegament induït → |
| Centre de pujada | Empenxa cap enrere, llançament |
| Final de pujada | Inversió d'ala, efecte mínim |

**Cadence desplaça la finestra de modulació** per alinear-se amb la fase on el braç de palanca aerodinàmic és més llarg. Cadència incorrecta = lluita contra la física de les ales. Cadència correcta = cada miliwatt es converteix en autoritat de control.

### Paràmetres

| Paràmetre | Valor | Funció |
|------------|-------|-----------|
| `ONDAS_K0` | 1.0 | Desplaçament de fase base |
| `ONDAS_K2` | 10,0 | Distribució de fases / nitidesa |
| `ONDAS_PHASE_SCALE` | 0,00005 | Factor petit, gran palanquejament |

---

## Ferocity P — Empensió asimètrica immediata

Ferocity P augmenta la **quadratitud de la forma d'ona** (forma trapezoïdal: residència a ±1, rampa cosinus entre) proporcionalment a l'error PID actual.

- Més empenta d'un costat → moment immediat
- L'ala frenada al final de la carrera experimenta **arrossegament induït** — aquest és el moment contrari
- Efecte: directe, proporcional, immediat

---

## Ferocity D — Explotació de l'arrossegament anticipat

Ferocity D completa la imatge. On P proporciona asimetria d'empenta, D aprofita la **arrossegament de l'ala contralateral** com a fre.

- Llegeix la taxa d'error de canvi i **anticipa**
- Pot explotar deliberadament l'arrossegament d'una ala alentida per a moments de guindada/cau
- P+D junts creen un **parell de moments diferencials** — empenta al costat A, arrossega al costat B — més eficient que només l'empenta

---

## Tres maneres Cadence/Ferocity D Augmenta Ferocity

### 1. El — D directe augmenta P durant el canvi ràpid d'error

En ratxes o maniobres agressives, `error_rate` és gran. D multiplica això i s'afegeix a la ferocitat de base. L'ala es torna *més nítida* (més trapezoïdal) perquè P+D junts demanen més quadrat que P sol. Resultat: màxima autoritat precisament quan és crític.

### 2. Indirecte — Cadence canvia el punt de palanquejament

Cadence modula *quan* en el cicle actua la ferocitat. Moure la finestra a una fase més sensible a l'aerodinàmica (p. ex., el centre de la carrera descendent versus l'extrem de la carrera amunt) significa que el **mateix valor de ferocitat** produeix una amplificació més efectiva — sense canvis numèrics.

### 3. Combinatòria — D × Cadence durant la recuperació de la parada

En una parada: alta taxa d'enfonsament → D detecta la velocitat → augmenta la ferocitat. Simultàniament, la cadència canvia la modulació a la fase de baixada on l'ala té la màxima mossegada. La interacció: D proporciona la força, la cadència el moment adequat. Sense cadència, la força D arriba a la fase equivocada i es dissipa inútilment.

---

## Paràmetres ONDAS addicionals

| Paràmetre | Funció |
|-----------|-----------|
| **Balance** | Simetria d'empenta cap amunt/baix — Biaix del terme I entre la carrera amunt i la baixada. Compensa la asimetria de les ales, les toleràncies de fabricació i el desgast |
| **Warp** | Rodament/Guanyada P → L/R Diferencial de ferocitat — Les ales dreta i esquerra baten de manera independent a l'eix de gir per a maniobres de inclinació i gir |
| **Anchor** | L'ancoratge de fase — bloqueja la modulació a una referència de fase específica, resistint la deriva |
| **Resonance** | La compensació de ressonància de la cèl·lula — evita els modes estructurals emocionants de la cèl·lula |

---

## Analogia

**Cadence és el director. Ferocity P i D són els instruments.**

Sense director, toquen — però no junts. Amb un, el soroll es converteix en música.

---

## Veure també

- [Guia d'afinació ONDAS](../../tutorials/ondas_tuning.html) procediment pràctic d'afinació —
- [Protocol MSP](msp.html) format de cable — per als paràmetres ONDAS
- [Perfils de vol](profiles.html) — Configuració ONDAS conscient del perfil