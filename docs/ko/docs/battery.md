# 배터리 모니터링

OrniFlight는 ADC(아날로그-디지털 변환기)를 통해 기본 배터리 전압을 모니터링합니다. 이를 통해 부저, LED 상태 및 LED 스트립 패턴을 통해 배터리 부족 경고를 활성화할 수 있습니다.

## 기능

- 연결 시 셀 수 자동 감지(최소/최대 셀 전압 기준)
- 구성 가능한 임계값을 통한 배터리 부족 경고
- mAh 소비에 대한 전류 감지(FC에서 지원하는 경우)
- OSD로 표시되고 원격 측정을 통해 전송되는 전압

## 지원되는 대상

지원되는 모든 비행 컨트롤러(OMNIBUSF4, TINYFISH)에는 전압 분배기를 통한 VBAT 모니터링이 포함됩니다.

## 연결

**항상 극성을 확인하십시오.** 연결하기 전에 예상되는 전압을 측정하십시오. 전압이 잘못되거나 극성이 바뀌면 비행 컨트롤러가 파손될 수 있습니다.

### OMNIBUSF4

메인 배터리를 VBAT 패드에 연결하세요. 온보드 전압 분배기는 최대 6S를 직접 처리합니다.

### TINYFISH

VBAT는 보드의 전원 입력 —를 통해 라우팅되며 별도의 연결이 필요하지 않습니다.

## CLI 설정

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## 안전

LiPo 배터리는 부하 상태에서 셀당 3.5V 미만으로 방전되어서는 안 됩니다. OrniFlight의 구성 가능한 임계값은 안전한 작동과 배터리 수명을 보장하는 데 도움이 됩니다.