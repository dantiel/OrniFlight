# 비디오 송신기(VTX)

OrniFlight는 FPV ornithopter에 대한 VTX 제어를 지원합니다. VTX 모듈은 OrniFlight 구성기, MSP 또는 CLI — 설정 대역, 채널, 전력 레벨 및 피트 모드를 통해 구성할 수 있습니다.

## 지원되는 프로토콜

1. **IRC Tramp** — 소형 VTX 모듈에 공통, 경량 FPV 오니톱터에 이상적
2. **TBS SmartAudio** — 피트 모드를 지원하는 디지털 프로토콜
3. **RTC6705** — VTX가 통합된 보드에서 직접 SPI 제어(예: SPRACINGF3NEO)

## 구성

VTX 설정은 OrniFlight 구성기의 **VTX** 탭 또는 CLI를 통해 관리됩니다.

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

## 직렬 포트

VTX 제어에는 전용 UART TX 핀이 필요합니다. `IRC Tramp` 또는 `TBS SmartAudio` 주변 장치를 사용하여 **포트** 탭에서 포트를 구성합니다.

## FPV Ornithopter 고려 사항

- 무게가 중요합니다. — 경량 VTX 모듈 선택(Tramp Nano, Eachine Nano)
- 안테나 장착 : 날개가 펄럭이는 공간 확보
- 전원 필터링: LC 필터 뒤에 VTX 전원을 연결하여 비디오의 서보 노이즈를 방지합니다.
- 소형 VTX 모듈의 과열을 방지하기 위해 벤치 테스트에는 피트 모드를 권장합니다.