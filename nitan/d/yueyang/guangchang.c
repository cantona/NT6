// Room: /d/yueyang/guangchang.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "廣場");
        set("long", @LONG
這是一個不大不小的青石廣場。廣場周圍是一些低矮的民房，南端
有一個戲台，戲台的雨篷被風雨吹得有些破敗，台上堆了不少雜物。廣
場上搭了不少小窩棚，看來有些凌亂。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"xijie",
        ]));
        set("objects", ([
                __DIR__"npc/liumang" : 1,
                CLASS_D("gaibang")+"/bangzhong" : 1,
        ]));
	set("coor/x", -6210);
	set("coor/y", -3020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}