//lhqdating.c
inherit ROOM;

void create()
{
        set("short", "烈火旗大廳");
        set("long", @LONG
這裡是烈火旗的大廳，廳中紅旗招展，刀槍映血，教眾絳衣赤帽，
團團擁住烈火旗掌旗使辛然。
LONG );
        set("exits", ([
                "west" : __DIR__"lhqyuan",
        ]));
        set("objects", ([
                __DIR__"npc/xinran": 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}