inherit ROOM;

void create()
{
        set("short", "大雪山口");
        set("long", @LONG
這裡冰天雪地，寒風刺骨。如果不是內力高深的人，已然經受不
住凍了。
LONG );
        set("exits", ([
                "northdown" : __DIR__"sroad5",
                "south"     : __DIR__"sroad7",
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}