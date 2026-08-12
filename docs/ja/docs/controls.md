# コントロール

OrniFlight uses standard RC stick mapping with ornithopter-specific extensions.

## スティックマッピング

|スティック |軸 |主な効果 |
|------|------|---------------|
|スロットル (左、垂直) |スロットル |羽ばたき振幅・推力 |
|ヨー (左、水平) |ヨー |旋回時の翼推力差 |
|ピッチ (右、垂直) |ピッチ |前傾/後傾 |
|ロール（右、水平） |ロール |左/右バンク |

## フライトモード

|モード |スティックの動作 |
|------|---------------|
| **ACRO** | Sticks control angular rate — no auto level |
| **ANGLE** | Sticks control angle — auto-level when released |
| **HORIZON** | ANGLE near center, ACRO at full deflection |

ACRO は経験豊富なパイロットにお勧めします。 ANGLE is good for first flights and thermal soaring.

## 羽ばたき装置固有の制御

### INDEPENDENTモード

When INDEPENDENT mode is active, each wing servo responds independently:
- **左スティック** → 左翼サーボ
- **右スティック** → 右翼サーボ
- Enables asymmetric flapping for aggressive maneuvers

### GLIDEモード

GLIDE mode locks both wings in horizontal position.羽ばたき飛行装置がグライダーになります。
- **スロットル**は翼の位置には影響しません
- **Pitch/Roll/Yaw** still influence tail control surfaces (if equipped)

### プロファイルの切り替え

In-flight profile switching via AUX channel allows changing PID/ONDAS parameters mid-flight:
- **プロファイル 1**: 標準クルーズ設定
- **プロファイル 2**: 高俊敏性設定
- **プロファイル 3**: 効率/滑空設定

## 料金

**PID チューニング** タブでレートを構成します。 For ornithopters, start with conservative rates — flapping dynamics amplify control inputs:
- RC レート: 0.80–1.00
- スーパーレート: 0.60–0.70
- エクスポ: 0.20–0.40