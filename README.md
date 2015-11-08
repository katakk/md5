# md5
md5 tool for Windows

## Windows 用のmd5sumツールです。

サーバーで md5sum *  としたときのハッシュチェックできることを目標としています。

らるちーはCRC16のみだったので。
ぶっちゃけ　らるちーのCRC16リスト比較は便利だったです・。

## バイナリ win 32

https://github.com/katakk/md5/blob/master/Release/md5.exe

# 高速化検討等

###ベンチマーク結果

あやねるDKのラジオCD vol2使った。結果 Crypto APIよりOpenBSD MD5+最適化のほうが速いので現状維持。
RSAなんとか呪文を書けば、FreeBSD由来のコードが使えてすこし早くなりそうなんだけどねw

| filname                                        | OpenBSD MD5         | Crypto API          |
|------------------------------------------------|---------------------|---------------------|
| 01-オープニング in あやねるーむ.wav            |    297 msec         |     531 msec        |
| 02-クイズ!一般常識チェック対決!!.wav           |   1047 msec         |    1875 msec        |
| 03-開催!お茶出し選手権!.wav                    |    703 msec         |    1265 msec        |
| 04-電話注文!_受け付けチャレンジ★.wav          |   1531 msec         |    2766 msec        |
| 05-ヒット確実!_売れるCM作り!.wav               |    688 msec         |    1219 msec        |
| 06-アフター5を楽しむ!女子会トーク&#9829;.wav   |    688 msec         |    1250 msec        |
| 07-エンディング.wav                            |    218 msec         |     390 msec        |

