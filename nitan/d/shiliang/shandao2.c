// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "山道");
        set("long", @LONG
這是一條崎嶇不平的山道，人跡罕至，聽說這裡不是很太平。
LONG
        );
        set("outdoors", "shiliang");
        set("exits", ([
                "southdown" : __DIR__"shandao1",
                "northup" : __DIR__"shandao3",
        ]));
        set("objects", ([
                __DIR__"npc/qingming" : 1,
        ]));
        set("coor/x", 1590);
        set("coor/y", -1980);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}