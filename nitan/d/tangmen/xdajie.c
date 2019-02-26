// Room: /tangmen/xdajie1.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long",
"一看就知道這就是唐家鎮的西大街了，向西就到了西門了。這是到蜀\n"
"中唐門的必由之路。大街的北邊就是有名的唐門酒樓了，唐門中人的婚宴\n"
"大多在這兒舉辦，老闆好像是江湖上有名的一朵花唐肥。\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([ 
                "west"  : __DIR__"ximen",
                "north" : __DIR__"jiulou",
                "east"  : __DIR__"zhongxin",
        ]));

        setup();
        replace_program(ROOM);
}
