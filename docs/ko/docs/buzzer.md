# 부저

OrniFlight는 상태 알림 및 분실 모델 위치 확인을 위한 활성 버저를 지원합니다.

## 기능

- **무장/무장 해제** — 고유 톤
- **배터리 부족** — 반복 경고음
- **안전 장치** — SOS 패턴
- **모델 분실** — 스위치를 통해 계속해서 경고음이 울림
- **GPS 수정** — 위성 잠금 장치의 확인음
- **보정** 자이로/가속 보정 중 — 경고음 패턴
- **RX 신호 손실** — 수신기 연결이 끊어지면 경고

## 하드웨어

- 5V 활성 버저(패시브 피에조 아님)를 **BUZZ-** 및 **BUZZ+** 패드에 연결합니다.
- 버저는 FC —의 트랜지스터로 구동되며 표준 버저에는 외부 드라이버가 필요하지 않습니다.

## CLI 설정

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```

## 오니톱터 안전

신호음은 키가 큰 풀이나 나뭇잎에 착지할 수 있는 대형 오니톱터에 특히 유용합니다. 필요할 때 빠르게 활성화하려면 임시 스위치에서 BEEPER 모드를 구성하세요.