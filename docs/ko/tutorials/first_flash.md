# 첫 번째 플래시

> *OrniFlight를 비행 컨트롤러 —에 단계별로 가져오기.*

## 필요한 것

- STM32F4 기반 비행 컨트롤러 (OMNIBUSF4, TINYFISH, MATEKF405 등)
- USB 케이블
- [dfu-util](http://dfu-util.sourceforge.net/) 또는 STM32CubeProgrammer
- [릴리스 페이지](https://github.com/dantiel/OrniFlight/releases)의 OrniFlight `.hex` 파일

## 1단계: DFU 모드로 전환

1. 비행 컨트롤러의 **BOOT 버튼**을 길게 누르세요.
2. **버튼을 누른 상태에서 USB**를 연결하세요.
3. 2초 후 **손을 떼세요**

macOS/Linux에서 확인:

```
dfu-util -l
```

`Found DFU: [0483:df11]`를 표시해야 함

## 2단계: 플래시

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## 3단계: 첫 번째 부팅

1. USB의 플러그를 뽑습니다.
2. USB를 다시 연결합니다(BOOT를 잡지 마세요).
3. OrniFlight 구성기를 통해 연결

## 4단계: 기본 구성

구성자에서:

1. **포트 탭**: 수신기에 대한 UART 구성(직렬 RX)
2. **구성 탭**: 수신기 프로토콜 선택(CRSF 권장)
3. **모드 탭**: ARM, GLIDE/INDEPENDENT 및 PROFILE 스위치 설정
4. **고급 → ONDAS 탭**: 기본값을 검토하고 먼저 Cadence를 조정합니다.

## 문제 해결

| 문제 | 수정 |
|---------|-----|
| DFU 장치를 찾을 수 없습니다 | 다른 USB 케이블을 사용해 보고 BOOT 버튼을 확인하세요 |
| 플래시 실패 | dfu-util 설치, USB 권한 확인 |
| 플래시 후 부팅되지 않음 | 다시 플래시하고 16진수가 목표와 일치하는지 확인 |
| 구성자가 연결되지 않음 | COM 포트 및 전송 속도 확인 |

---

*다음: [기본 설정](basic_setup.html) →*