// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "走廊");
        set ("long", @LONG
這是一條長長的走廊。走廊西邊是萬府大廳。東邊的盡頭是個小客堂。
LONG);
        set("region", "jingzhou");
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/qifang" : 1,
        ]));
        set("exits", ([
                "south"  : __DIR__"wan_dating",
                "north"  : __DIR__"wan_ketang",
        ]));

        set("coor/x", -7110);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (!objectp(present("hu cheng", me)) &&
                dir == "north" &&
                objectp(present("qi fang", environment(me))))
                return notify_fail("戚芳攔住你説：我夫君中毒卧牀，請勿打擾。\n");

        return ::valid_leave(me, dir);
}