//shuige2.c                四川唐門—亭榭水閣

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "亭榭水閣");
        set("long",
"這裏是蓮藕小築的亭榭水閣。這裏與蓮藕小築連為一體，同樣是古玉\n"
"色的建築。水閣四壁上繪着各色的山水魚蟲，這裏再往前就是蓮雲閣了！\n"
);
        set("exits", ([
                "north" : __DIR__"lianyunge",
                "south" : __DIR__"shuige1",  
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}