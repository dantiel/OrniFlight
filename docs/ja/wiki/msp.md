# MSP プロトコル

> *MultiWii シリアル プロトコル — コンフィグレータが OrniFlight と通信する方法。*

## 概要

OrniFlight は、鳥飛行装置固有のメッセージを使用して Betaflight MSP を拡張します。正式な仕様は、`src/main/msp/` のファームウェア リポジトリにあります。

**現在のバージョン:** apiVersion 1.46 (OrniFlight v0.4.6)

## 重要なメッセージ

### MSP_PID_ADVANCED (112 / 0x70)

メインの ONDAS チューニング メッセージ。 48 バイト (レガシー) から 87 バイト (1.46) に増加しました。

| API バージョン |サイズ |新しいコンテンツ |
|---------------|------|---------------|
| 1.33 | 48 |レガシー PID アドバンスト |
| 1.42 | 59 | + itermRelaxCutoff、ONDAS v2 で 10 のゲイン |
| 1.43 | 71 | + servo_mount_angle[4]、phase_shift[4]、prescience、espelho、saudade、ssff |
| 1.44 | 75 | + サーボ速度、最大振幅、フラップ振幅、翼原点オフセット[4] |
| 1.45 | 82 | + freq_channel、freq_min_hz、freq_max_hz、flight_mode、flutter_gain、flutter_hz、throttle_bypass |
| 1.46 | 87 | + プロファイルインデックス、フェロシティ_ダウンストローク、フェロシティ_アップストローク、エアロエラスティック_グライド、エアロエラスティック_フラップ |

### MSP_SERVO_CONFIGURATIONS (120 / 0x78)

4 ONDAS の末尾バイトを含むサーボ構成: glide_deg + ONDAS v1 トリプレット。

## 下位互換性

すべての API バージョンには下位互換性があります。 48 バイトの送信者は 1.46 の受信者と通信します。— 追加フィールドのデフォルトは適切な値です。

## ワイヤー形式

すべてのマルチバイト値はリトルエンディアンです。符号付きの値は、回線上に `value + 128` として保存されます。符号なしゲイン値 (0–100) は直接値です。配列の長さの前に u8 カウントが付きます。

---

*完全な仕様については、ファームウェア リポジトリの `docs/MSP_FIRMWARE_INTERFACE.md` を参照してください。*