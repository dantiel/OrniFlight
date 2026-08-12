# フライトプロファイル

> *4 つの独立したチューニング スロット、飛行中に切り替え可能。*

## コンセプト

OrniFlight は 4 つの完全な `ornithopterProfile_t` 構造体 — を格納し、それぞれに 19 個の ONDAS および翼ダイナミクス パラメーターがすべて含まれています。 BOX モード (`BOXORNITHOPTERPROFILE`、permanentId 52) は、4 つのスロット (0–3) にマップされた 2 ポジションの RC スイッチを介してアクティブなプロファイルを選択します。

## なぜプロファイルなのか?

飛行体制が異なれば、異なる調整が必要になります。

|プロフィール |使用例 | Cadence | Ferocity |メモ |
|----------|----------|----------|----------|----------|
| 0 | **クルーズ** |ミッド (50) |低 (30) |効率的な前進飛行 |
| 1 | **曲技飛行** |低 (20) |高 (80) |最大権限 |
| 2 | **ホバー/徘徊** |高 (70) |ミッド (50) |速度よりも安定性 |
| 3 | **グライド** |ミッド (50) |低 (10) |最小限の介入 |

## プロフィールの内容

`ornithopterProfile_t` の 19 フィールドすべて:

- **グライド ジオメトリ**: glide_angle
- **ONDAS v2 (10)**: ケイデンス、ferocity_d/p/roll/yaw、バランス、ワープ、warp_yaw、アンカー、レゾナンス
- **Phase 2 (4)**: 先見性、エスペリョ、サウダージ、SSFF
- **波形 (2)**: ferocity_downbottom 、ferocity_upbottom ストローク
- **Aeroelastic (2)**: aeroelastic_glide_coefficient、aeroelastic_flap_coefficient

## グローバルとは (プロファイルごとではない)

- 周波数チャンネル (RC チャンネル 1 つ、INDEPENDENT と GLIDE の両方で動作)
- サーボマウント角度
- フラッピング位相シフト
- GralhaAzul ジオメトリ (servo_speed、max_amplitude、flap_magnitude、wing_origin)

これらは機体の物理定数 — であり、飛行体制によっては変化しません。

## 飛行中の切り替え

1. 2 ポジションまたは 3 ポジションのスイッチを予備チャンネルに割り当てます
2. [Configurator Modes] タブで、その範囲を `ORNITHOPTER PROFILE` にマップします。
3. 各スイッチ位置は 4 つのスロットの 1 つを選択します。
4. コンフィギュレータのプロファイル ドロップダウンは、MSP 経由で *現在選択されている* スロットを編集します

---

*構造体の定義については、`src/main/flight/ornithopter_profile.h` を参照してください。*