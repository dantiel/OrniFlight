#!/usr/bin/env python3
"""Complete Japanese translation — poetic/hermetic style for the manifest."""
import json, os

path = os.path.expanduser("~/Desktop/HOI_KOSMOI/paraeksperiment/OrniFlight/docs/_lang/ja.json")
with open(path) as f:
    ja = json.load(f)

# ── Hero ──
ja["hero_greeting"] = "羽ばたき飛行、再定義。"
ja["hero_version"] = "STM32F3 ◇ OrniFlight v0.4.6 ◇ API v1.46"

# ── Manifest (poetic, hermetic) ──
ja["manifest_body"] = (
    "自然は、最初のクアッドコプターが離陸するより1億5千万年前に、羽ばたき飛行を解いていた。"
    "すべての雀が、すべてのアホウドリが、すべてのハチドリが、その神経系に飛行の理を宿している——"
    "いかなるPID制御器も未だ再現し得ない理を。"
    "OrniFlightは新たなる領域を開く——推力は位相であり、安定は律動であり、機体は羽搏きのたびに呼吸する。"
    "ONDAS——我らが<strong>振動正規化動的適応安定化</strong>は、羽ばたき空気力学の第一原理から構築された初の制御理論である。"
    "それは矯正力を羽搏きの<em>内側</em>で変調する——抗うことなく、無視することなく、<strong>共に</strong>あるのだ。"
    "このファームウェアは自由ソフトウェアである——なぜなら飛行はいかなる企業にも属さないからだ。"
    "市販のSTM32F3で動作する——なぜなら超越的飛行の道具は一食の夕べより安価であるべきだからだ。"
    "OrniFlightは戦火を潜り抜けた設計を受け継ぎ、未踏の空へと踏み出す——"
    "<strong>飛行制御装置の新種</strong>、翼のためにシリコンから構築されたもの。"
    "鳥たちは、我々が追いつくのを待っていたのだ。"
)

# ── ONDAS body ──
ja["ondas_body"] = (
    "クアッドPIDは連続推力を前提とする。鳥型機の推力は<strong>位相的</strong>である——"
    "同じ力積が、羽搏きの<em>どの瞬間</em>に作用するかによって異なるモーメントを生む。"
    "ONDASはカデンツァ、獰猛さ、非対称性、ワープ、錨、共鳴、予見、エスペーリョ、サウダーデ、"
    "そしてSSFF——位相を識る変調器たちの管弦楽——をもって、修正の一グラム一グラムを、"
    "空気力学が活かせる正確な場所へと配置する。"
)

# ── Feature descriptions ──
ja["feat_profiles_desc"] = (
    "4つの独立したプロファイル（0〜3）、BOXモードで飛行中に切替可能。"
    "各プロファイルは完全なONDAS調整、波形形状、空力弾性係数を保持する。"
)

ja["feat_frequency_desc"] = (
    "最小/最大Hzのマッピングを持つ単一RCチャンネル。"
    "INDEPENDENTモードとGLIDEモードで同一に動作——ひとつのつまみで両方の飛行領域を司る。"
)

ja["feat_gralhaazul_desc"] = (
    "台形波形生成、サーボ速度制限、振幅マッピング、フラップ振幅、翼起点幾何学——"
    "翼運動方程式の中核。"
)

ja["feat_ondas_desc"] = (
    "カデンツァタイミング、3軸の獰猛さP/D、バランス、ワープ、錨、共鳴——"
    "プロファイルごとにMSP経由でリアルタイム調整可能。"
)

ja["feat_msp_desc"] = (
    "完全なONDAS調整GUI——19のプロファイルフィールドすべて、周波数チャンネル、"
    "GralhaAzul、フェーズ2ゲイン。スロットごとの編集のためのプロファイル切替機能。"
)

ja["feat_glide_desc"] = (
    "2つの飛行領域：GLIDE（スロットル中心、自然な滑空）と"
    "INDEPENDENT（RCチャンネル経由の直接フラップ周波数）。BOX選択可能。"
)

# ── Hardware ──
ja["hw_lead"] = (
    "サーボ対応タイマーピンを備えた、Betaflight 4.0互換の"
    "任意のSTM32F3/F4/F7フライトコントローラーで動作。"
)

# ── Build ──
ja["build_compatible"] = (
    "GPL v3 ◇ Betaflight 4.0.6より分岐 ◇ クリーンビルド：警告ゼロ"
)

# ── Footer ──
ja["footer_credit"] = "OrniFlight —— 羽ばたき飛行、再定義。"
ja["footer_resources"] = (
    '<a href="https://github.com/dantiel/OrniFlight" target="_blank">GitHub</a>'
    ' ◇ <a href="en/wiki/">Wiki</a>'
    ' ◇ <a href="en/tutorials/">Tutorials</a>'
    ' ◇ <a href="https://github.com/dantiel/orniflight-configurator" target="_blank">Configurator</a>'
)

# ── Also refine existing short strings for better Japanese ──
ja["manifest_lead"] = (
    "OrniFlightが存在する理由——羽ばたく翼は推力、ピッチ、ロール、ヨーを"
    "<strong>一打のうちに</strong>制御するからだ。"
    "いかなるプロペラも敵わない表現力の回路である。"
)

ja["ondas_lead"] = (
    "<strong>振動正規化動的適応安定化</strong>——"
    "羽ばたき空気力学のために特別に構築された初の制御理論。"
)

with open(path, "w") as f:
    json.dump(ja, f, ensure_ascii=False, indent=2)
    f.write("\n")

print("✅ Japanese translation complete")
