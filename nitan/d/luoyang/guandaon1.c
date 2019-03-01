inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
這是一條寬闊筆直，塵土飛揚的大官道，足可容得下十馬並馳。南邊
不遠是東都洛陽古城的北門，往北直上可以到達華山。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"guandaon2",
                  "south" : __DIR__"nbridge",
        ]));

        setup();
        replace_program(ROOM);
}