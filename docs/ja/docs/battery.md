# バッテリー監視

OrniFlight は、ADC (アナログ - デジタル コンバーター) を介してメイン バッテリーの電圧を監視します。これにより、ブザー、ステータス LED、および LED のストリップ パターンによるバッテリー低下の警告が有効になります。

## 特徴

- 接続時のセル数の自動検出 (最小/最大セル電圧に基づく)
- 設定可能なしきい値によるバッテリー低下警告
- mAh消費量の電流検出(FCでサポートされている場合)
- 電圧は OSD に表示され、テレメトリ経由で送信されます

## サポートされているターゲット

サポートされているすべてのフライト コントローラー (OMNIBUSF4、TINYFISH) には、分圧器を介した VBAT モニタリングが含まれています。

## 接続

**常に極性を確認してください。** 接続する前に予想される電圧を測定してください。電圧が間違っていたり、極性が逆になったりすると、フライト コントローラーが破損します。

### OMNIBUSF4

メインバッテリーをVBATパッドに接続します。オンボード分圧器は最大 6S までを直接処理します。

### TINYFISH

VBAT はボードの電源入力 — を介して配線され、別個の接続は必要ありません。

## CLI 設定

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## 安全性

LiPo バッテリーは、負荷がかかった状態でセルあたり 3.5V 未満で放電してはなりません。 OrniFlight の構成可能なしきい値は、安全な操作とバッテリー寿命の確保に役立ちます。