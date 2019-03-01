inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
這是一條寬闊筆直，塵土飛揚的大官道，足可容得下十馬並馳。南邊
是東都洛陽古城，往北直上可以到達華山。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : "/d/village/hsroad1",
                  "south" : __DIR__"guandaon3",
        ]));

        setup();
        replace_program(ROOM);
}