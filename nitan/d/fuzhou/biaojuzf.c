// Room: /d/fuzhou/biaojuzf.c
// Date: may.12 1998 Java

inherit ROOM;

void create()
{
        set("short", "賬房");
        set("long", @LONG
這裏是福威鏢局的賬房，地上鋪着大紅地毯，壁上字畫高懸。上首
一張紅木交椅，上坐一個老先生。一古木書案橫於椅前，上面整齊的堆
着一卷卷鏢局押鏢的貨票。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "west"   : __DIR__"biaojuzt",
                "south"  : __DIR__"biaojuhc",
        ]));
        set("objects", ([
                __DIR__"npc/huang" : 1,
        ]));
	set("coor/x", -91);
	set("coor/y", -6161);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}