// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "西樓");
        set ("long", @LONG
這是萬老爺子住的地方。擺設簡單整潔，右首一張木床。方磚地上
有幾處凹凸，顯是主人勤于習武所致。
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "north" : __DIR__"wan_shufang",
                "east"  : __DIR__"wan_dating",
        ]));

        set("no_clean_up", 0);
        set("coor/x", -7120);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}