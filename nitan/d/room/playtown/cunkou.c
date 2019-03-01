// by 山貓ADX @ snow 99-12-4

#include <ansi.h>
inherit ROOM;

void create ()
{
        set("short",  "村口");
        set("long",
"這裡就是"HBRED WHT"『泥潭』"NOR+
"的玩家村。這裡非常的安靜，看來玩家們都在忙\n"
"著挖泥巴，真是累啊！\n"
);
        set("exits",  ([
                "north"  :  __DIR__"guandao8",
                "south"  :  __DIR__"road14",
        ]));
        set("outdoors",  1);
        setup();
        replace_program(ROOM);
}