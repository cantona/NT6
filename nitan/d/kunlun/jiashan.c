// Room: /d/kunlun/jiashan.c
// Last Modified by winder on Nov. 15 2000

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "假山");
        set("long", @LONG
穿過了九曲廊就到了這裡，黃色的山拔地而起，山峰俊俏，山間古
柏，山頂小亭，山中還有小院、石橋、石室等，氣勢磅礡。為江南山石
中所少見。
LONG );
        set("exits",([
                "east"      : __DIR__"qishi",
                "west"      : __DIR__"houting",
                "southwest" : __DIR__"jiuqulang5",
                "northwest" : __DIR__"huayuan",
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119980);
        set("coor/y", 40120);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}