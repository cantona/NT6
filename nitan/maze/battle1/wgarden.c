// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIC"山谷"NOR);
        set("long", @LONG
這是一個山谷，山谷裏異種花卉甚是不少。百花爭放，山石古拙，
楊柳垂清，蒼松翠竹，景緻煞是宜人。清澈的溪流旁聳立着一座小亭子，
潺潺溪水向西南流去。
LONG);
        set("exits", ([ /* sizeof() == 3 */
                "south": __DIR__"wzoulan",
                "east" : __DIR__"room_01",
                "out" : __DIR__"wgate",
        ]));

        set("outdoors", "battle");
        setup();
}
