//houroad2.c                四川唐門─青石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青石小路");
        set("long",
"這裡是後宅西側的青石小路。隱隱的可以聽到遠處傳來清脆的流水聲\n"
"，展目望去已經可以看見在風中搖擺的片片荷葉。一陣清風吹過帶來一股\n"
"荷花清香。\n"
);
        set("exits", ([
                        "west" : __DIR__"houroad3",
                        "east" : __DIR__"houroad1",
                        "northwest" : __DIR__"yaofang",
                        "southwest" : __DIR__"ycailiao",
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}