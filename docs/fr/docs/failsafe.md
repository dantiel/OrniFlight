# Sécurité intégrée

OrniFlight dispose d'un système de sécurité en deux étapes pour protéger votre ornithoptère en cas de perte du signal du récepteur.

## Système à deux étages

### Perte de signal — de l'étape 1 détectée

Déclenché lorsque :
- Tout canal de vol a une longueur d'impulsion invalide
- Le récepteur signale le mode de sécurité
- Aucun signal du récepteur pendant une durée configurée

**Action** : Tous les canaux passent aux valeurs de repli (configurées via `rxfail`). Une courte fenêtre de récupération commence — si le signal revient, le vol normal reprend.

### Temps de garde — de l'étape 2 expiré

Entré lorsque l'étape 1 persiste plus longtemps que `failsafe_delay` (par défaut : 400 ms) ET que le vaisseau est armé.

**Procédures** (configurables via `failsafe_procedure`) :

| Procédure | Comportement |
|-----------|----------|
| **DROP** | Désarmez immédiatement les ailes de — s'arrêtent, l'avion descend |
| **LAND** | Mode plané ailes — verrouillées horizontalement, descente contrôlée |

**LAND** est la procédure recommandée pour les ornithoptères —. Elle maintient les ailes en position neutre pour une descente planée, ce qui laisse le temps de récupérer le signal.

## CLI Paramètres

```
set failsafe_delay = 4         # Guard time in 0.1s (4 = 400ms)
set failsafe_procedure = LAND  # DROP or LAND
set failsafe_throttle = 1000   # Fallback throttle (low)
set failsafe_switch_mode = STAGE1  # Transmitter switch behavior
```

## Sécurité intégrée du récepteur

Configurez également la sécurité intégrée de votre récepteur pour qu'elle n'émet **aucune impulsion** en cas de perte de signal. Cela permet au contrôleur de vol de détecter la perte et d'activer l'étape 1.

## Tests

Test de sécurité **avec tringlerie d'aile déconnectée** sur banc :
1. Attribuez le mode FAILSAFE à un commutateur
2. Armez l'engin
3. Basculez l'interrupteur → et observez la procédure de sécurité.
4. Vérifiez que le comportement du servo correspond aux attentes