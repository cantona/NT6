//exiaolu2.c                四川唐門─碎石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "碎石小路");
        set("long",
"這裡是後山小路。道路越來越窄，雜草卻更加茂密已經齊腰高矮不時\n"
"從遠處傳來聲聲怪嘯，讓人頭皮發麻，小路彎彎曲曲的向前伸去通向更加\n"
"陰暗的後山。\n"
);
        set("exits", ([
                        "west" : __DIR__"exiaolu1",
                        "eastup" : __DIR__"houshan",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}