// shulin.c
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
       set("short",HIY"山陵"NOR);
       set("long", @LONG
突然之間，西北方出現了一片山陵，山上樹木蒼蔥，在戈壁中突然看到，
真如見到世外仙山一般。大戈壁上丘陵起伏，幾個沙丘將這片山陵遮住了，
因此遠處完全望不見。
LONG);
        set("exits", ([
                "west" : __DIR__"gebi2",
                "south" : __DIR__"gebi1",
                "east" : __DIR__"gebi4",
                "northwest" : __DIR__"shulin1",
        ]));
        set("outdoors", "hasake");
        set("no_quest",1);
        setup();
       replace_program(ROOM);
}