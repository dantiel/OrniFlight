# Batteriövervakning

OrniFlight övervakar huvudbatteriets spänning via ADC (Analog-to-Digital Converter). Detta möjliggör varningar för låg batterinivå genom summer, status LED och LED stripmönster.

## Funktioner

- Autodetektering av cellantal vid anslutning (baserat på min/max cellspänningar)
- Varning för lågt batteri med konfigurerbara trösklar
- Strömavkänning för mAh-förbrukning (om det stöds av FC)
- Spänning visas i OSD och sänds via telemetri

## Mål som stöds

Alla flygkontroller som stöds (OMNIBUSF4, TINYFISH) inkluderar VBAT-övervakning via spänningsdelare.

## Anslutningar

**Kontrollera ALLTID POLARITETEN.** Mät förväntad spänning innan du ansluter. Felaktig spänning eller omvänd polaritet kommer att förstöra din flygkontroll.

### OMNIBUSF4

Anslut huvudbatteriet till VBAT pad. Spänningsdelaren ombord hanterar upp till 6S direkt.

### TINYFISH

VBAT leds genom kortets strömingång — ingen separat anslutning behövs.

## CLI Inställningar

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## Säkerhet

LiPo-batterier bör aldrig laddas ur under 3,5V per cell under belastning. OrniFlight konfigurerbara trösklar hjälper till att säkerställa säker drift och batterilivslängd.