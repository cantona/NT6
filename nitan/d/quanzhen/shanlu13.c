// /d/quanzhen/shanlu13.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條非常崎嶇難行的山路，一路蜿蜒盤山ㄦ上，沿途均是葱
鬱的古柏山林，蔚然森秀。在此處可眺望終南山的景色，只見山險嶺
峻，山川毓秀，不少鳥ㄦ在枝頭高聲啼唱不絕。往北下是草堂寺。往
西上是一條山路。往東是一塊廣大的空地。往西北通往後山下。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "westup"     : "/d/gumu/shanlu6",
                "northdown"  : __DIR__"caotangsi",
                "northwest"  : __DIR__"shandao1",
                "eastdown"   : __DIR__"daxiaochang",
        ]));

        set("coor/x", -3180);
        set("coor/y", 110);
        set("coor/z", 130);
        setup();
        replace_program(ROOM);
}