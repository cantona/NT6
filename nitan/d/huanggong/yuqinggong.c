// yuqinggong.c

inherit ROOM;

void create()
{
        set("short", "毓慶宮");
        set("long", @LONG
這兒是皇太子讀書的地方. 太子年幼, 不肯用功, 於是皇上就找來
一些皇族的幼兒來陪太子.
LONG
        );
        set("exits", ([
                "north"   : __DIR__"fengxianmen",
                "east"    : __DIR__"huangjimen",
                "west"    : __DIR__"rijing",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2800);
	set("coor/y", 7741);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}