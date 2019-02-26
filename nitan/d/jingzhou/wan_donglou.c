// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "東樓");
        set ("long", @LONG
這是萬門弟子住的地方。萬門一共有八個弟子，除第三個弟子萬圭
外，其餘的都住在這裏。牆上掛了幾把刀劍。
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "west"   : __DIR__"wan_dating",
                "north"  : __DIR__"wan_chaifang",
        ]));
        set("objects", ([
                __DIR__"npc/shencheng" : 1,
                __DIR__"npc/sunjun"    : 1,
                __DIR__"npc/boyuan"    : 1,
                __DIR__"npc/fengtan"   : 1,
        ]));

        set("coor/x", -7100);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}