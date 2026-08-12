# 비행 프로필

> *4개의 독립적인 튜닝 슬롯, 기내에서 전환 가능.*

## 컨셉

OrniFlight는 각각 19개의 ONDAS 및 날개 역학 매개변수를 모두 포함하는 4개의 완전한 `ornithopterProfile_t` 구조체 —를 저장합니다. BOX 모드(`BOXORNITHOPTERPROFILE`, 영구 ID 52)는 4개 슬롯(0–3)에 매핑된 2위치 RC 스위치를 통해 활성 프로필을 선택합니다.

## 왜 프로필인가?

비행 체제에 따라 다른 튜닝이 필요합니다.

| 프로필 | 사용 사례 | Cadence | Ferocity | 메모 |
|---------|----------|---------|----------|-------|
| 0 | **크루즈** | 미드(50) | 낮음 (30) | 효율적인 전진 비행 |
| 1 | **곡예비행** | 낮음 (20) | 높음 (80) | 최대 권한 |
| 2 | **호버/로이터** | 높음 (70) | 미드(50) | 속도보다 안정성 |
| 3 | **글라이드** | 미드(50) | 낮음 (10) | 최소한의 개입 |

## 프로필에는 무엇이 들어있나요?

`ornithopterProfile_t`의 모든 19개 필드:

- **글라이드 지오메트리**: glide_angle
- **ONDAS v2 (10)**: 케이던스, ferocity_d/p/roll/yaw, 밸런스, 워프, warp_yaw, 앵커, 공명
- **Phase 2 (4)**: 예지력, espelho, saudade, ssff
- **파도 모양(2)**: ferocity_downstrom, ferocity_upstrok
- **공탄성(2)**: aeroelastic_glide_coefficient, aeroelastic_flap_coefficient

## 전역이란 무엇입니까(프로필별이 아님)

- 주파수 채널(RC 채널 1개, INDEPENDENT 및 GLIDE 모두에서 작동)
- 서보 마운트 각도
- 플래핑 위상 변화
- GralhaAzul 형상(servo_speed, max_amplitude,flap_magnitude,wing_origin)

이것은 비행 체제에 따라 변하지 않는 기체 —의 물리적 상수입니다.

## 비행 중 전환

1. 2위치 또는 3위치 스위치를 예비 채널에 할당합니다.
2. 구성자 모드 탭에서 해당 범위를 `ORNITHOPTER PROFILE`에 매핑합니다.
3. 각 스위치 위치는 4개의 슬롯 중 하나를 선택합니다.
4. 구성기의 프로필 드롭다운은 MSP를 통해 *현재 선택된* 슬롯을 편집합니다.

---

*구조체 정의는 `src/main/flight/ornithopter_profile.h`를 참조하세요.*