# 수신기(RX)

OrniFlight는 ornithopter의 무선 제어를 위한 다중 수신기 프로토콜을 지원합니다.

## 지원되는 프로토콜

| 프로토콜 | 유형 | 메모 |
|----------|------|-------|
| **CRSF** (크로스파이어) | 연재 | 낮은 대기 시간, 원격 측정 권장 |
| **SBUS** | 연재 | 반전됨, F4에 인버터가 필요함 |
| **IBUS**(FlySky) | 연재 | 비반전, 직접 UART |
| **PPM** | 단일 와이어 아날로그 | 8ch, 레거시, 권장되지 않음 |
| **SPEKTRUM** | 연재 | 1024/2048, CLI를 통해 바인딩 |
| **FPORT** | 연재 | FrSky, RX+원격 측정 결합 |
| **GHST** (유령) | 연재 | ImmersionRC, 낮은 대기 시간 |

## 시리얼 RX 구성

1. 무료 UART RX 핀에 수신기를 연결합니다.
2. 구성기 → **포트**에서: UART를 `Serial RX`로 설정합니다.
3. 구성기 → **구성**에서 프로토콜을 선택합니다.
4. F4의 SBUS의 경우: `set sbus_inversion = ON`를 활성화합니다.

## CLI 빠른 설정

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```

## 안전장치

수신기가 신호 손실 시 **펄스 없음**을 출력하도록 수신기 안전 장치를 구성합니다. 그러면 비행 컨트롤러가 이를 감지하고 자체 안전 장치 절차를 활성화합니다. FC 수준 구성은 [안전 장치](failsafe.html)를 참조하세요.