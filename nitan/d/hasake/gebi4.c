// gebi1.c
#include <room.h>
inherit ROOM;
void create()
{
       set("short","西域大戈壁");
       set("long", @LONG
這是西域的大戈壁，要走出這裏並非易事。不遠處塵土沙粒鋪天蓋
地般吹來，看來要起風暴了。
LONG);
        set("exits", ([
                "north" : __DIR__"gebi2",
                "south" : __DIR__"gebi3",
                "east" : __DIR__"gebi1",
                "west" : __FILE__,
        ]));
        set("outdoors", "hasake");
        set("no_quest",1);
        setup();
}
#include "gebi.h";