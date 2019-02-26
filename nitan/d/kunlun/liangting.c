// Room: /d/kunlun/liangting.c
// Last Modified by winder on Nov. 15 2000

#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
         set("short", "涼亭");
         set("long", @LONG
這是湖中的一個小亭子，從這望去，可以看到整個湖面的景色，令
人心曠神怡。陣陣涼風吹來，好一片江南春色，令人忘了這裏是西域絕
頂。
LONG );
         set("exits",([
                "east"      : __DIR__"houting",
                "west"      : __DIR__"qinshi",
                "southeast" : __DIR__"jiuqulang5",
                "northeast" : __DIR__"huayuan",
        ]));
        set("outdoors", "kunlun");
        set("no_clean_up", 0);
        set("coor/x", -120000);
        set("coor/y", 40120);
        set("coor/z", 90);
        setup();   
        replace_program(ROOM);
}