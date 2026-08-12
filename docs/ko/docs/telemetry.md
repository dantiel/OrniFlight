# 원격 측정

원격 측정은 OrniFlight에서 무선 송신기 — 배터리 전압, 전류, RSSI, GPS 좌표, 고도 등의 비행 데이터를 보냅니다.

## 지원되는 프로토콜

| 프로토콜 | 무선 시스템 | 와이어 수 |
|------------|-------------|------------|
| **CRSF** | 크로스파이어/트레이서/ELRS | RX와 통합(양방향) |
| **SmartPort** | FrSky | 1선(TX 핀) |
| **HoTT** | 그라우프너 | 1선(TX+TZ) |
| **IBUS** | FlySky | 1선(센서 TX) |
| **LTM** | 가벼운 원격 측정(MWP) | 1선(TX) |

## 구성

1. 구성기 → **포트**에서: UART TX 핀을 적절한 원격 측정 프로토콜로 설정합니다.
2. 원격 측정 기능 활성화: `feature TELEMETRY`
3. 필요한 경우 원격 측정 반전을 구성합니다.

**CRSF**의 경우 원격 측정은 — 별도의 포트가 필요 없이 자동으로 처리됩니다.

## SmartPort (FrSky)

SmartPort는 F4 프로세서에서 신호 반전이 필요합니다. 다음 중 하나:
- 인버터가 내장된 비행 컨트롤러 사용
- `set tlm_inversion = ON`와 함께 SoftSerial 사용

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```

## 원격 측정 데이터

OrniFlight는 다음을 전송합니다:
- VBAT 전압(메인 배터리)
- 현재 소모량 / mAh 소모
- RSSI (신호 강도)
- 비행 모드 / 팔 상태
- GPS 좌표(사양 적용 시)
- 고도/바리오(기압계인 경우)
- ONDAS 비행 프로필이 활성화되었습니다.