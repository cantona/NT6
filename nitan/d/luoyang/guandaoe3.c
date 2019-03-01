inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
這是一條寬闊筆直，塵土飛揚的大官道，足可容得下十馬並馳。往東
通向函谷關可以達揚州城，往西則可以到達東都洛陽古城。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"guandaoe2",
                  "east" : __DIR__"guandaoe4",
        ]));

        setup();
        replace_program(ROOM);
}