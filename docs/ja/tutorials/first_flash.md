#ファーストフラッシュ

> *OrniFlight をフライト コントローラー — に段階的に追加します。*

## 必要なもの

- STM32F4 ベースのフライト コントローラー (OMNIBUSF4、TINYFISH、MATEKF405 など)
- USBケーブル
- [dfu-util](http://dfu-util.sourceforge.net/) または STM32CubeProgrammer
- [リリース ページ](https://github.com/dantiel/OrniFlight/releases) からの OrniFlight `.hex` ファイル

## ステップ 1: DFU モードに入る

1. フライト コントローラーの **BOOT ボタンを押し続けます**
2. ボタンを押したまま **USB** を接続します
3. 2 秒後に **手を放します**

macOS/Linux で確認します。

```
dfu-util -l
```

`Found DFU: [0483:df11]` と表示されるはずです

## ステップ 2: フラッシュ

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## ステップ 3: 最初の起動

1.USBのプラグを抜きます
2. USB を再び差し込みます (BOOT を長押ししないでください)
3. OrniFlight コンフィギュレーター経由で接続する

## ステップ 4: 基本構成

コンフィギュレータで:

1. **ポート タブ**: レシーバーの UART を設定します (シリアル RX)
2. **「構成」タブ**: 受信機プロトコルを選択します (CRSF を推奨)
3. **[モード]タブ**: ARM、GLIDE/INDEPENDENT、および PROFILE スイッチを設定します。
4. **高度な → ONDAS タブ**: デフォルトを確認し、最初に Cadence を調整します

## トラブルシューティング

|問題 |修正 |
|----------|-----|
| DFU デバイスが見つかりません |別の USB ケーブルを試し、BOOT ボタンを確認してください。
|フラッシュが失敗する | dfu-util のインストール、USB 権限を確認してください。
|フラッシュ後に起動しない |再フラッシュし、16 進数がターゲットと一致することを確認します。
|コンフィギュレーターが接続できない | COM ポートとボーレートを確認してください。

---

*次へ: [基本設定](basic_setup.html) →*