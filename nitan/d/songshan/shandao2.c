// Room: /d/songshan/shandao2.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "嵩岳山道");
        set("long", @LONG
你走在嵩岳山道，青鬆翠柏，山風嵐霧，時來飄盪。遠望山下犬吠
雞啼，頓起仙凡之感。
LONG );
        set("exits", ([
                "northup"   : __DIR__"shuyuan",
                "southdown" : __DIR__"qimushi",
        ]));
        set("objects", ([
                __DIR__"npc/sima": 1,
        ]));
        set("outdoors", "songshan");
        set("coor/x", -10);
        set("coor/y", 760);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}