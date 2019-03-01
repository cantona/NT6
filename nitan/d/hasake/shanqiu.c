// shanqiu.c 小山丘

inherit ROOM;

void create()
{
        set("short", "小山丘");
        set("long", @LONG
這裡是草原和森林的分界線，往西可以看到高聳如雲的天山山脈和從
這裡一直延伸出去的針葉林，往東可以看見部族的跑馬場，還隱隱可以聽
見哈薩克族人的話語。
LONG);        
        set("exits", ([
            "eastdown" : __DIR__"road",
            "south" : __DIR__"caoyuan9",
            "north" : __DIR__"caoyuan9",
            "westdown" : __DIR__"senlin1",
        ]));

        set("objects", ([
                         __DIR__"npc/bird" : 1,
                         __DIR__"npc/supu" : 1,
        ]));

        set("outdoors", "hasake");
        
        setup();
        replace_program(ROOM);
}