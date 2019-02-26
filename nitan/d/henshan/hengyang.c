inherit ROOM;

void create()
{
        set("short", "衡陽城");
        set("long", @LONG
這裏就是衡陽縣城。衡陽地處偏遠，顯見遠不如中原繁華了。
LONG );
        set("outdoors", "henshan");

        set("exits", ([
               "east"   : __DIR__"hengyang2",
               "west"   : __DIR__"hengyang1",
               "south"  : __DIR__"chaguan",
               "north"  : __DIR__"lingxingmen",
        ]));

        set("objects", ([
                "/d/henshan/npc/lu" : 1,
        ]));
	set("coor/x", -6890);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}