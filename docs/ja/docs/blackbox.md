# ブラックボックスロギング

Blackbox は、飛行後の分析、調整、デバッグのために飛行データを記録します。 OrniFlight は、オンボード フラッシュ チップまたは外部 OpenLog デバイスへのロギングをサポートします。

## ログに記録される内容

- **ジャイロ** — 生およびフィルタリングされた 3 軸角速度
- **加速度計** — 3 軸加速度
- **PID 出力** — 軸ごとの P、I、D、F 寄与
- **ONDAS** — Cadence、Ferocity P/D、およびその他のフラッピング固有のパラメーター
- **RC コマンド** — レート/エクスポ後のスティック位置
- **サーボ出力** — 各サーボチャンネルへの最終出力
- **バッテリー** — 反復あたりの電圧と電流
- **GPS** — 位置、速度、高度 (利用可能な場合)

## セットアップ

### オンボードフラッシュ (OMNIBUSF4)

OMNIBUSF4 には、Blackbox ログ用の 16MB オンボード フラッシュが含まれています。コンフィギュレータで有効にする:

1. **ブラックボックス** タブ → `Blackbox logging device` を `Onboard flash` に設定します
2. ロギング レートを設定します (推奨: F4 ターゲットの場合は N=2 ～ 4 の `1/N`)
3. ロギングの開始/停止にスイッチを割り当てます。

### 外部 OpenLog

OpenLog を空き UART TX ピンに接続します。

1. **ポート** タブ → UART を 115200 ボーで `Blackbox logging` に設定します
2. OpenLog を接続します: FC TX → OpenLog RX、プラス 5V/GND

## 分析ツール

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — Webベースのログビューア
- カスタム分析のために `blackbox_decode` — を CSV に変換します

## ONDAS 固有

Blackbox は、ONDAS パラメータを調整するために不可欠です。ログに記録される ONDAS データには次のものが含まれます。
- `ondas_cadence_phase` — 変調ウィンドウ タイミング
- `ondas_ferocity_p` / `ondas_ferocity_d` — 非対称推力コンポーネント
- `ondas_balance` — 左右ウイングバランス
- 各反復におけるサーボごとの出力

これにより、羽ばたき機構の正確な分析と翼の非対称修正が可能になります。