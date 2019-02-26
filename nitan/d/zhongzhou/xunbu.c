inherit ROOM;

void create()
{
        set("short", "巡捕房");
        set("long", @LONG
一走進昏暗的巡捕房，一時你啥都看不見，就覺得有點陰
森可怕。你飛快的想着自己有沒做過什麼傷天害理的事。
LONG);
        set("objects", ([
                  "clone/npc/xunbu" : 2,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"laofang",
                  "west" : __DIR__"wendingbei3",
        ]));

        set("coor/x", -9030);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}