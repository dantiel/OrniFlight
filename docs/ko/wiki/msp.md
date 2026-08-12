# MSP 프로토콜

> *MultiWii 직렬 프로토콜 — 구성자가 OrniFlight와 통신하는 방법.*

## 개요

OrniFlight는 ornithopter 관련 메시지로 Betaflight MSP를 확장합니다. 신뢰할 수 있는 사양은 zz0zzz의 펌웨어 저장소에 있습니다.

**현재 버전:** apiVersion 1.46(OrniFlight v0.4.6)

## 핵심 메시지

### MSP_PID_ADVANCED (112 / 0x70)

주요 ONDAS 튜닝 메시지입니다. 48바이트(레거시)에서 87바이트(1.46)로 증가했습니다.

| API 버전 | 사이즈 | 새로운 콘텐츠 |
|---------------|------|-------------|
| 1.33 | 48 | 레거시 PID 고급 |
| 1.42 | 59 | + itermRelaxCutoff, 10 ONDAS v2 이득 |
| 1.43 | 71 | + Servo_mount_angle[4], Phase_shift[4], prescience, espelho, saudade, ssff |
| 1.44 | 75 | + 서보 속도, 최대 진폭, 플랩 크기, 날개 원점 오프셋[4] |
| 1.45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, flight_mode, flutter_gain, flutter_hz, throttle_bypass |
| 1.46 | 87 | + 프로필 인덱스, 페로시티_다운스트로크, 페로시티_업스트로크, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120 / 0x78)

4 ONDAS 후행 바이트가 있는 서보 구성: glide_deg + ONDAS v1 삼중항.

## 이전 버전과의 호환성

모든 API 버전은 이전 버전과 호환됩니다. 48바이트 발신자는 1.46 수신자와 통신합니다. — 추가 필드의 기본값은 합리적인 값입니다.

## 와이어 형식

모든 멀티바이트 값은 리틀 엔디안입니다. 연결에 `value + 128`로 저장된 서명된 값입니다. 부호 없는 이득 값(0–100)은 직접적입니다. u8 개수 앞에 배열 길이가 있습니다.

---

*전체 사양은 펌웨어 저장소의 `docs/MSP_FIRMWARE_INTERFACE.md`를 참조하세요.*