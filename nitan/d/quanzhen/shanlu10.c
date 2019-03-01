// /d/quanzhen/shanlu10.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條非常崎嶇難行的山路，一路蜿蜒盤山ㄦ上，沿途均是葱
鬱的古柏山林，蔚然森秀。在此處可眺望終南山的景色，只見山險嶺
峻，山川毓秀，不少鳥ㄦ在枝頭高聲啼唱不絕。往東下是蓮花寺。往
西上是一條山路。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "westup"    : __DIR__"riyueyan",
                "eastdown"  : __DIR__"jinliange",
        ]));

        set("coor/x", -3140);
        set("coor/y", 30);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}