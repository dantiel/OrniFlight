# 믹서

믹서는 비행 컨트롤러 출력(롤, 피치, 요, 스로틀)을 ornithopter의 서보 신호로 변환합니다.

## 오니톱터 믹서

OrniFlight는 ornithopter 전용 구성으로 Betaflight의 믹서 시스템을 확장합니다. 믹서는 다음을 처리합니다.

- **윙 서보**: PID 출력을 윙 스트로크 변조로 변환
- **테일 서보**(옵션): 엘리베이터/방향타 표면 제어

## 믹서 유형

| 믹서 | 사용 사례 |
|-------|----------|
| **ORNITHOPTER** | 2개의 날개 서보를 갖춘 표준 이중 날개 오니톱터 |
| **ORNITHOPTER_4S** | 4서보 오니톱터(좌/우 독립 날개 제어) |
| **ORNITHOPTER_TAIL** | 이중 날개 + 테일 엘리베이터 + 방향타 |

## 서보 구성

**Servos** 탭 또는 CLI를 통해 구성됩니다.

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## ONDAS 통합

믹서는 ONDAS(Ornithopter Nonlinear Dynamic Aerodynamic System)와 함께 작동합니다.

- **스로틀** →는 기본 플래핑 진폭을 설정합니다.
- **ONDA Cadence** →는 각 스트로크 내에서 변조 창을 이동합니다.
- **ONDA Ferocity** →는 스트로크 파형 모양을 수정합니다(정현파 ↔ 사다리꼴)
- **ONDA Balance** → 왼쪽/오른쪽 날개 대칭 수정

자세한 ONDAS 이론은 [ONDAS Wiki](../wiki/ondas.html)를 참조하세요.

## CLI 설정

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```