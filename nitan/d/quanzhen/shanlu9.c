// /d/quanzhen/shanlu9.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條非常崎嶇難行的山路，一路蜿蜒盤山ㄦ上，沿途均是葱
鬱的古柏山林，蔚然森秀。在此處可眺望終南山的景色，只見山險嶺
峻，山川毓秀。往北上走是金蓮閣。往南走是崎嶇的山路。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "northup"   : __DIR__"jinliange",
                "southdown" : __DIR__"shanlu8",
        ]));

        set("coor/x", -3130);
        set("coor/y", 20);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}