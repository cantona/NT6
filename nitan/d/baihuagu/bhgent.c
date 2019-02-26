// Room: /d/baihuagu/bhgent.c
// Last Modified by Winder on Mar. 5 2001

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIW"茫茫雪地");
        set("long",
HIW"這裏是白茫茫的一片雪地，" NOR"遠處山峯層巒迭嶂。前面隱隱約約
好像有一個山谷。陣陣花香飄過來，好象還夾雜着鳥的歡唱。\n"
        );
        set("outdoors", "baihuagu");
        set("exits", ([ 
                "south" : __DIR__"out",
                "north" : __DIR__"huagu1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -380);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}