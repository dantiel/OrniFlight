# RSSI

RSSI(수신 신호 강도 표시기)는 라디오 링크의 품질을 보여줍니다. OrniFlight는 아날로그 입력, 직렬 수신기 데이터 또는 프로토콜 RSSI에서 RSSI를 소싱할 수 있습니다.

## RSSI 소스

| 소스 | 연결 | 구성 |
|---------|------------|---------------|
| **직렬 프로토콜** | 없음(직렬 RX 와이어 사용) | CRSF, GHST — 자동 |
| **AUX 채널** | 없음(TX는 RSSI를 채널로 보냄) | `set rssi_channel = 8` |
| **아날로그 ADC** | FC → 수신기의 RSSI 패드 RSSI 출력 | `set rssi_adc_channel = 1` |

## 구성

### 직렬 RSSI(CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI는 추가 배선이 필요하지 않은 직렬 프로토콜 —에 의해 자동으로 전송됩니다.

### 아날로그 RSSI

비행 컨트롤러에 수신기 RSSI 출력 → RSSI 패드 연결:

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX 채널 RSSI

특정 채널에서 RSSI를 보내도록 송신기를 구성한 후:

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## 디스플레이

RSSI는 OSD에 표시되며 원격 측정을 통해 라디오로 전송될 수 있습니다. 경고 임계값을 구성합니다.

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## 오니톱터 범위

ornithopter의 경우 RSSI는 — 날개를 펄럭이는 날개가 역동적인 RF 간섭 패턴을 만드는 데 중요합니다. 초기 테스트 비행 중에 RSSI를 모니터링하여 모든 날개 위치에서 안정적인 링크 성능을 확인하십시오.