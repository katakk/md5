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

あやねるDKのラジオCD vol2使った。

再測定結果 Crypto APIのほうが速いので変えます。


| MD5                              | filname                                        | OpenBSD 1.11   | Crypto API     |
|----------------------------------|------------------------------------------------|----------------|----------------|
| 6c9a52399177c5d3d0abc2ad04298b5c | 01-オープニング in あやねるーむ.wav            |   484 msec     |   282 msec     |
| d20af68a067be2fbf5156c57c85cfa59 | 02-クイズ!一般常識チェック対決!!.wav           |  1672 msec     |  1047 msec     |
| 434b80c0c9a52d067974d468eb02303a | 03-開催!お茶出し選手権!.wav                    |  1141 msec     |   703 msec     |
| 9dc81fff88b7e764d25877779a151e2b | 04-電話注文!_受け付けチャレンジ★.wav          |  2453 msec     |  1516 msec     |
| ca8d6087e472a0a77aff318fe4a3d8f8 | 05-ヒット確実!_売れるCM作り!.wav               |  1078 msec     |   688 msec     |
| 670525c1e5e9cb39e98a8a493d49f3a1 | 06-アフター5を楽しむ!女子会トーク&#9829;.wav   |  1110 msec     |   687 msec     |
| 55cf7a0f7f8e46f0b8dbf35510b0cf40 | 07-エンディング.wav                            |   343 msec     |   219 msec     |
                                                                                                                                     
# OpenBSD MD5
http://cvsweb.openbsd.org/cgi-bin/cvsweb/src/lib/libc/hash/md5.c
##OpenBSD: md5.c,v 1.11
 msec

# Crypto API
Windows自体が持っている暗号化ライブラリ

