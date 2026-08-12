# 직렬 포트

OrniFlight는 주변 장치(수신기, GPS, 원격 측정, VTX 제어, 블랙박스 로깅 및 MSP(구성기 연결))와의 통신을 위해 직렬 포트를 사용합니다.

## 직렬 포트 유형

| 유형 | 설명 | 최고의 대상 |
|------|------------|----------|
| **VCP** | USB 가상 COM 포트 — 프로세서에 직접 USB 연결 | 구성기(MSP) |
| **UART** | 하드웨어 신호 감지 기능이 있는 하드웨어 TX/RX 핀 | RX, GPS, 원격 측정, VTX, 블랙박스 |
| **SoftSerial** | 모든 핀 쌍의 소프트웨어 기반 직렬 | 낮은 대역폭: 원격 측정 전용 |

VCP는 물리적 UART —를 소비하지 않으며 구성자에서 항상 사용할 수 있습니다.

## 포트 할당

OrniFlight 구성기에서 **포트** 탭으로 이동하여 기능을 할당합니다.

| 기능 | 전형적인 UART | 메모 |
|----------|-------------|-------|
| 직렬 RX | UART1 또는 UART3 | SBUS, CRSF, IBUS 등 |
| GPS | UART3 또는 UART6 | 57600 또는 115200 보드 |
| 원격 측정 | 모든 TX 핀 | SmartPort, HoTT, IBUS |
| VTX(부랑자/SmartAudio) | 모든 TX 핀 | 단일 와이어 |
| 블랙박스 | 모든 TX 핀 | OpenLog 또는 온보드 플래시 |
| MSP | VCP(USB) | 구성기 연결 |

## OMNIBUSF4 포트 매핑

| UART | 핀 | 일반적인 용도 |
|------|------|------------|
| VCP | USB | MSP(구성자) |
| UART1 | TX1/RX1 | 시리얼 RX |
| UART3 | TX3/RX3 | GPS 또는 원격 측정 |
| UART6 | TX6/RX6 | 무료 / 블랙박스 / VTX |

## SoftSerial

SoftSerial를 사용할 수 있지만 대역폭이 제한되어 있습니다. 저속 원격 측정(예: 9600 보드 SmartPort)에만 적합합니다. 직렬 RX 또는 GPS에는 권장되지 않습니다.