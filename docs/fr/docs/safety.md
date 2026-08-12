# Sécurité

## Liste de contrôle avant le vol

1. **Ailes** : assurez-vous que les ailes sont solidement montées et que la liaison est intacte.
2. **Batterie** : Entièrement chargée, correctement sécurisée, nombre de cellules correct
3. **Contrôles** : Vérifiez les réponses du stick dans l'onglet Récepteur du configurateur
4. **Failsafe** : Test sur banc avant le vol (voir [Failsafe](failsafe.html))
5. **Arm Switch** : configurez et testez —, ne comptez jamais uniquement sur l'armement du stick.
6. **Zone de lancement** : dégagée de personnes, d'obstacles et d'obstacles aériens

## Sécurité des bras

OrniFlight utilise plusieurs sécurités avant d'armer :

- **Throttle low** : l'accélérateur doit être au minimum
- **Niveau** : L'engin doit être raisonnablement de niveau
- **RX Signal** : signal de récepteur valide requis
- **CPU Load** : Le système ne doit pas être surchargé
- **Calibration** : L'accéléromètre et le gyroscope doivent être calibrés

## Sécurité en vol

- **Volez en visibilité directe**
- Maintenir une distance de sécurité avec les personnes et les animaux
- Surveiller la tension de la batterie — atterrit avant le seuil d'avertissement
- En FPV : volez toujours avec un observateur
- Vent : les ornithoptères peuvent être sensibles au vent — connaissez vos limites

## Procédures d'urgence

| Situation | Actions |
|-----------|--------|
| Perte d'orientation | Passez en mode INDEPENDENT, sticks centraux |
| Perte de signal | Failsafe atterrira automatiquement (si la procédure LAND est configurée) |
| Dommages aux ailes | Désarmez immédiatement les ailes — s'arrêtent |
| Impact d'oiseaux | Désarmer, évaluer les dégâts avant de réarmer |
| Batterie faible | Atterrissez immédiatement. Les ornithoptères — n'ont pas d'autorotation |

## Risques spécifiques aux ornithoptères

- **Risque de pincement** : le battement des ailes peut causer des blessures. — gardez les mains dégagées lorsqu'il est armé.
- **Défaillance de liaison** : vérifiez avant le vol toutes les tiges de poussée et les rotules
- **Resonance** : Certaines fréquences de battement peuvent exciter les résonances de la cellule. — réglez le balayage ONDAS pour éviter
- **Verrouillage du plané** : Si les servos des ailes tombent en panne dans une position non neutre, l'atterrissage contrôlé est impossible. — testez les positions de sécurité des servos.