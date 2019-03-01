// Room: /d/shaolin/hanshuim.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "漢水");
        set("long", @LONG
這是漢水的貨運渡船，波濤翻滾的江水將船搖得一晃一晃的。但
是船夫們將船操得穩穩的，不出一點岔子。
LONG );

        set("no_fight", 1);
        set("outdoors", "nanyang");
        set("region", "nanyang_zone");
        setup();
        replace_program(ROOM);
}