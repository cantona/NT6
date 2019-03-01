// gebi1.c
#include <room.h>
inherit ROOM;
void create()
{
       set("short","西域大戈壁");
       set("long", @LONG
這是西域的大戈壁，要走出這裡並非易事。不遠處塵土沙粒舖天蓋
地般吹來，看來要起風暴了。
LONG);
        set("exits", ([
                "north" : __DIR__"gebi2",
                "south" : __DIR__"gebi3",
                "east" : __DIR__"gebi4",
                "west" : __FILE__,
        ]));
        set("no_quest",1);
        set("outdoors", "hasake");
        setup();
}
#include "gebi.h";