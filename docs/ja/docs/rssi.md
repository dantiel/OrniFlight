#RSSI

RSSI (受信信号強度インジケーター) は、無線リンクの品質を示します。 OrniFlight は、アナログ入力、シリアル受信機データ、またはプロトコル RSSI から RSSI をソースできます。

## RSSI ソース

|出典 |接続 |構成 |
|------|-----------|------|
| **シリアル プロトコル** |なし (シリアル RX ワイヤ経由) | CRSF、GHST — 自動 |
| **AUX チャンネル** |なし (TX はチャネルとして RSSI を送信します) | `set rssi_channel = 8` |
| **アナログ ADC** | RSSI パッドオン FC → レシーバー RSSI 出力 | `set rssi_adc_channel = 1` |

## 構成

### シリアル RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI はシリアル プロトコル — によって自動的に送信され、追加の配線は必要ありません。

### アナログ RSSI

受信機 RSSI 出力 → RSSI パッドをフライト コントローラーに接続します。

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX チャンネル RSSI

特定のチャネルで RSSI を送信するように送信機を設定し、次の手順を実行します。

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## ディスプレイ

RSSI は OSD に表示され、テレメトリ経由で無線に送信できます。警告しきい値を構成します。

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## 羽ばたき飛行範囲

鳥飛行装置の場合、RSSI は重要です。— 羽ばたく翼は、動的な RF 干渉パターンを作成します。最初のテスト飛行中に RSSI を監視して、翼のすべての位置で信頼できるリンク パフォーマンスを検証します。