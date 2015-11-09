# md5
md5 tool for Windows

## Windows 用のmd5sumツールです。

サーバーで md5sum *  としたときのハッシュチェックできることを目標としています。

らるちーはCRC16のみだったので。
ぶっちゃけ　らるちーのCRC16リスト比較は便利だったです・。

## バイナリ win 32

https://github.com/katakk/md5/blob/master/Release/md5.exe

なまえをsha1.exeに変えるとsha1になるよ

# 高速化検討等

###ベンチマーク結果

あやねるDKのラジオCD vol2使った。

再測定結果 Crypto APIのほうが速いので変えます。


| filname                                        | OpenBSD 1.11   | Crypto API     |
|------------------------------------------------|----------------|----------------|
| 01-オープニング in あやねるーむ.wav            |   391 msec     |  188 msec      |
| 02-クイズ!一般常識チェック対決!!.wav           |   672 msec     |  469 msec      |
| 03-開催!お茶出し選手権!.wav                    |   484 msec     |  468 msec      |
| 04-電話注文!_受け付けチャレンジ★.wav          |  1203 msec     |  797 msec      |
| 05-ヒット確実!_売れるCM作り!.wav               |   516 msec     |  312 msec      |
| 06-アフター5を楽しむ!女子会トーク&#9829;.wav   |   531 msec     |  360 msec      |
| 07-エンディング.wav                            |   203 msec     |  109 msec      |


| MD5                              | filname                                        |
|----------------------------------|------------------------------------------------|
| 6c9a52399177c5d3d0abc2ad04298b5c | 01-オープニング in あやねるーむ.wav            |
| d20af68a067be2fbf5156c57c85cfa59 | 02-クイズ!一般常識チェック対決!!.wav           |
| 434b80c0c9a52d067974d468eb02303a | 03-開催!お茶出し選手権!.wav                    |
| 9dc81fff88b7e764d25877779a151e2b | 04-電話注文!_受け付けチャレンジ★.wav          |
| ca8d6087e472a0a77aff318fe4a3d8f8 | 05-ヒット確実!_売れるCM作り!.wav               |
| 670525c1e5e9cb39e98a8a493d49f3a1 | 06-アフター5を楽しむ!女子会トーク&#9829;.wav   |
| 55cf7a0f7f8e46f0b8dbf35510b0cf40 | 07-エンディング.wav                            |

# OpenBSD MD5
http://cvsweb.openbsd.org/cgi-bin/cvsweb/src/lib/libc/hash/md5.c

| filname | v1.11     | v1.10     | v1.9      | v1.8      | v1.7      | v1.6      | v1.5      | v1.4      | v1.3      | v1.2      | v1.1      |
|---------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
| 01      |  391 msec |  391 msec |  250 msec |  281 msec |  250 msec |  422 msec |  281 msec |  219 msec |  328 msec |  391 msec |  281 msec |
| 02      |  672 msec |  781 msec |  750 msec |  859 msec |  875 msec |  922 msec |  813 msec |  953 msec |  844 msec | 1171 msec |  781 msec |
| 03      |  484 msec |  563 msec |  563 msec |  641 msec |  484 msec |  469 msec |  593 msec |  563 msec |  547 msec |  516 msec |  734 msec |
| 04      | 1203 msec |  625 msec | 1406 msec | 1453 msec | 1157 msec | 1203 msec | 1047 msec | 1250 msec | 1328 msec | 1328 msec | 1407 msec |
| 05      |  516 msec |  562 msec |  422 msec |  547 msec |  453 msec |  500 msec |  563 msec |  437 msec |  531 msec |  594 msec |  593 msec |
| 06      |  531 msec |  531 msec |  500 msec |  687 msec |  547 msec |  641 msec |  719 msec |  485 msec |  469 msec |  500 msec |  625 msec |
| 07      |  203 msec |  172 msec |  140 msec |  250 msec |  218 msec |  250 msec |  156 msec |  296 msec |  172 msec |  141 msec |  188 msec |


# Crypto API
Windows自体が持っている暗号化ライブラリ

