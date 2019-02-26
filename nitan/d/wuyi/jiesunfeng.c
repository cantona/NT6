// Room: /d/wuyi/jiesunfeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "接筍峯");
        set("long", @LONG
“鳳髓鸞膠天上有，世人休作等閒看”。接筍峯貼壁而立，三道裂
痕清晰可見，彷彿三塊巖石粘合而成，似有搖搖欲墜之態，令人望而生
畏。它又稱小隱屏，峭削無比，尖鋭直上，形同立筍。橫裂三痕，彷彿
續界而成，奇妙而險峻。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"shaibuyan",
                "south" : __DIR__"yunwo",
        ]));
        set("objects", ([
                "/d/taishan/npc/dao-ke" : 1,
        ]));
        set("coor/x", 1360);
        set("coor/y", -5000);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
