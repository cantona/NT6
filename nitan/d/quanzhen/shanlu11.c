// /d/quanzhen/shanlu11.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條非常崎嶇難行的山路，一路蜿蜒盤山ㄦ上，沿途均是蔥
鬱的古柏山林，蔚然森秀。在此處可眺望終南山的景色，只見山險嶺
峻，山川毓秀，不少鳥ㄦ在枝頭高聲啼唱不絕。往南下是兩塊聳天而
立的巨石。往北是一片蓊鬱的山林。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "northup"    : __DIR__"shulin1",
                "southdown"  : __DIR__"riyueyan",
        ]));

        set("coor/x", -3150);
        set("coor/y", 40);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}