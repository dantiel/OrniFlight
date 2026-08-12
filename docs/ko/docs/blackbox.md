# 블랙박스 로깅

Blackbox는 비행 후 분석, 튜닝 및 디버깅을 위해 비행 데이터를 기록합니다. OrniFlight는 온보드 플래시 칩 또는 외부 OpenLog 장치에 대한 로깅을 지원합니다.

## 기록되는 내용

- **자이로** — 원시 및 필터링된 3축 각속도
- **가속도계** — 3축 가속
- **PID 출력** — 축당 P, I, D, F 기여
- **ONDAS** — Cadence, Ferocity P/D 및 기타 플래핑 관련 매개변수
- **RC 명령** rate/expo 이후 — 스틱 위치
- **서보 출력** 각 서보 채널에 — 최종 출력
- **배터리** — 반복당 전압 및 전류
- **GPS** — 위치, 속도, 고도(사용 가능한 경우)

## 설정

### 온보드 플래시(OMNIBUSF4)

OMNIBUSF4에는 블랙박스 로깅을 위한 16MB 온보드 플래시가 포함되어 있습니다. 구성기에서 활성화:

1. **블랙박스** 탭 → `Blackbox logging device`를 `Onboard flash`로 설정
2. 로깅 속도 설정(권장: F4 대상의 경우 N=2-4인 `1/N`)
3. 로깅 시작/중지 스위치 할당

### 외부 OpenLog

OpenLog를 무료 UART TX 핀에 연결합니다:

1. **포트** 탭 → 115200 보드에서 UART를 `Blackbox logging`로 설정합니다.
2. OpenLog 연결: FC TX → OpenLog RX 및 5V/GND

## 분석 도구

- [블랙박스 탐색기](https://github.com/betaflight/blackbox-log-viewer) — 웹 기반 로그 뷰어
- `blackbox_decode` —는 사용자 정의 분석을 위해 CSV로 변환됩니다.

## ONDAS-특정

ONDAS 매개변수를 튜닝하려면 블랙박스가 필수적입니다. 기록된 ONDAS 데이터에는 다음이 포함됩니다.
- `ondas_cadence_phase` — 변조 창 타이밍
- `ondas_ferocity_p` / `ondas_ferocity_d` — 비대칭 추력 구성 요소
- `ondas_balance` — 왼쪽/오른쪽 윙 밸런스
- 각 반복마다 서보별 출력

이를 통해 날개짓 역학과 날개 비대칭 수정을 정밀하게 분석할 수 있습니다.