# md5
md5 tool for Windows

Windows 用のmd5sumツールです。


サーバーで md5sum *  としたときのハッシュチェックできることを目標としています。

らるちーはCRC16のみだったので。
ぶっちゃけ　らるちーのCRC16リスト比較は便利だったです・。

https://github.com/katakk/md5/blob/master/Release/md5.exe


Crypto APIよりOpenBSD MD5+最適化のほうが速いので現状維持。

ベンチマーク結果

 ** OpenBSD MD5

6c9a52399177c5d3d0abc2ad04298b5c  01-オープニング in あやねるーむ.wav [297 msec]
d20af68a067be2fbf5156c57c85cfa59  02-クイズ!一般常識チェック対決!!.wav [1047 msec]
434b80c0c9a52d067974d468eb02303a  03-開催!お茶出し選手権!.wav [703 msec]
9dc81fff88b7e764d25877779a151e2b  04-電話注文!_受け付けチャレンジ★.wav [1531 msec]
ca8d6087e472a0a77aff318fe4a3d8f8  05-ヒット確実!_売れるCM作り!.wav [688 msec]
670525c1e5e9cb39e98a8a493d49f3a1  06-アフター5を楽しむ!女子会トーク?.wav [688 msec]
55cf7a0f7f8e46f0b8dbf35510b0cf40  07-エンディング.wav [218 msec]

 **
 ** Crypto API
 **

6c9a52399177c5d3d0abc2ad04298b5c  01-オープニング in あやねるーむ.wav [531 msec]
d20af68a067be2fbf5156c57c85cfa59  02-クイズ!一般常識チェック対決!!.wav [1875 msec]
434b80c0c9a52d067974d468eb02303a  03-開催!お茶出し選手権!.wav [1265 msec]
9dc81fff88b7e764d25877779a151e2b  04-電話注文!_受け付けチャレンジ★.wav [2766 msec]
ca8d6087e472a0a77aff318fe4a3d8f8  05-ヒット確実!_売れるCM作り!.wav [1219 msec]
670525c1e5e9cb39e98a8a493d49f3a1  06-アフター5を楽しむ!女子会トーク?.wav [1250 msec]
55cf7a0f7f8e46f0b8dbf35510b0cf40  07-エンディング.wav [390 msec]

