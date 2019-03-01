//jingshifang.c

inherit ROOM;

void create()
{
        set("short", "敬事房");
        set("long", @LONG
這是宮內的監辦處, 是宮中太監的管理機構, 太監總管都在此地.
LONG
        );
        set("exits", ([
                "northeast" : __DIR__"qianqinggong",
        ]));
        set("objects", ([
                __DIR__"npc/hai": 1,
                __DIR__"npc/xiaoguizi": 1,
        ]));
	set("coor/x", -2820);
	set("coor/y", 7741);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}