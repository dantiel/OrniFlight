# ビデオトランスミッター (VTX)

OrniFlight は、FPV 羽ばたき飛行装置の VTX 制御をサポートします。 VTX モジュールは、OrniFlight コンフィギュレーター、MSP、または CLI — 設定バンド、チャンネル、パワー レベル、およびピット モードを介して構成できます。

## サポートされているプロトコル

1. **IRC Tramp** — 小型の VTX モジュールに共通、軽量の FPV 羽ばたき飛行装置に最適
2. **TBS SmartAudio** — ピットモードサポート付きデジタルプロトコル
3. **RTC6705** — VTX が統合されたボード上の直接 SPI 制御 (例: SPRACINGF3NEO)

## 構成

VTX 設定は、OrniFlight Configurator の **VTX** タブ、または CLI 経由で管理されます。

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

## シリアルポート

VTX 制御には専用の UART TX ピンが必要です。 [**ポート**] タブでポートを `IRC Tramp` または `TBS SmartAudio` ペリフェラルで構成します。

## FPV 羽ばたき飛行装置に関する考慮事項

- 重量は重要です — 軽量の VTX モジュールを選択してください (Tramp Nano、Eachine Nano)
- アンテナの取り付け: 羽ばたきからのクリアランスを確保
- 電源フィルタリング: ビデオ内のサーボノイズを避けるために、LC フィルタの後に VTX 電源を接続します。
- 小型VTXモジュールの過熱を避けるため、ベンチテストにはピットモードをお勧めします