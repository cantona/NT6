//houshan.c                四川唐門─後山

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "後山");
        set("long",
"這裡是蓮雲閣後山。這裡陰森恐怖，四周密林叢生，連日光也被遮住\n"
"，地上樹影斑駁，林中好象有無數兇狠的目光注視著你，可能隨時會撲上\n"
"來殺死你，趕快離開這裡吧！\n"
);
        set("exits", ([
                        "northdown" : __DIR__"shanshi1",
                        "westdown" : __DIR__"exiaolu2",
                        "eastup" : __DIR__"shandao1",
                        "southdown" : __DIR__"shanshi6",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}