# GPS

GPS는 ornithopter에 대한 위치 유지, 홈 복귀 및 원격 측정 기반 탐색을 지원합니다. OrniFlight의 GPS 기능은 기능적이지만 실험적인 것으로 간주됩니다. —는 항상 시각적 시야 내에서 비행합니다.

## 지원되는 프로토콜

- **UBLOX** (권장) — UBlox 바이너리 프로토콜, 효율적이고 안정적
- **NMEA** — 텍스트 기반 표준 프로토콜

## 하드웨어

- BN-880, BN-220 또는 유사한 UBlox M8N GPS+Compass 모듈
- 연결: TX/RX를 무료 UART 및 5V/GND에 연결
- 간섭을 최소화하기 위해 GPS를 전원 전선 및 서보 케이블에서 멀리 장착하십시오.
- 나침반/자력계는 자기원(전선, 서보)에서 멀리 떨어져 있어야 합니다.

## 구성

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```

1. **Ports** 탭에서 GPS에 직렬 포트를 할당합니다(UBlox의 경우 기본 115200 보드).
2. GPS 기능 활성화
3. 공급자 설정
4. 저장 후 재부팅

## OSD 요소

OSD에 표시되는 GPS 데이터는 다음과 같습니다.
- 위성 수 및 수정 유형
- GPS 좌표(위도/경도)
- 대지 속도
- 고도(GPS)
- 집과의 거리
- 홈 방향 화살표

## 오니톱터 고려사항

- GPS 안테나는 하늘이 맑아야 합니다. — 장착 위치는 날개가 펄럭이는 데 매우 중요합니다.
- 작은 오니톱터에서는 무게 패널티가 상당합니다.
- GPS 지원 RTH(홈으로 돌아가기)는 날개짓하는 비행 역학을 위해 탐색 PID 값을 주의 깊게 조정해야 합니다.