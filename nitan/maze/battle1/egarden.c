// This program is a part of NT MudLIB
// /d/arenahuang/egarden.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIC"山谷"NOR);
        set("long", @LONG
這是一個山谷，山谷裡異種花卉甚是不少。百花爭放，山石古拙，
楊柳垂清，蒼鬆翠竹，景致煞是宜人。清澈的溪流旁聳立著一座小亭子，
潺潺溪水向西南流去。
LONG);
        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"ezoulan",
                "west" : __DIR__"room_09",
                "out" : __DIR__"egate",
        ]));

        set("outdoors", "battle");
        setup();
}
