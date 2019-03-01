inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
這是一條寬闊筆直，塵土飛揚的大官道，足可容得下十馬並馳。往南
通可以達襄陽城，往北不遠便是東都洛陽古城了。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"guandaos1",
                  "south" : __DIR__"guandaos3",
                "east"  : __DIR__"guanlin",
        ]));

	set("coor/x", -6990);
	set("coor/y", 2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}