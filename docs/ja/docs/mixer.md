# ミキサー

ミキサーは、フライト コントローラーの出力 (ロール、ピッチ、ヨー、スロットル) を鳥飛行装置のサーボ信号に変換します。

## 羽ばたき飛行ミキサー

OrniFlight は、Betaflight のミキサー システムを鳥飛行装置固有の構成で拡張します。ミキサーは以下を処理します。

- **翼サーボ**: PID 出力を翼ストローク変調に変換します。
- **テールサーボ** (オプション): エレベーター/ラダー面を制御します。

## ミキサーの種類

|ミキサー |使用例 |
|------|----------|
| **ORNITHOPTER** | 2 つの翼サーボを備えた標準的な双翼羽ばたき飛行装置 |
| **ORNITHOPTER_4S** | 4サーボ羽ばたき飛行装置（左右翼独立制御） |
| **ORNITHOPTER_TAIL** |デュアルウイング + テールエレベーター + ラダー |

## サーボ構成

[**サーボ**] タブまたは CLI 経由で構成します。

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## ONDAS の統合

ミキサーは、ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System) と連携して動作します。

- **スロットル** → は基本のフラッピング振幅を設定します
- **ONDA Cadence** → は各ストローク内で変調ウィンドウをシフトします
- **ONDA Ferocity** → はストローク波形の形状を変更します (正弦波 ↔ 台形)
- **ONDA Balance** → 左右翼の対称性補正

ONDAS 理論の詳細については、[ONDAS Wiki](../wiki/ondas.html) を参照してください。

## CLI 設定

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```