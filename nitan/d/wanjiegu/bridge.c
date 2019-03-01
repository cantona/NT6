// Room: /t/wanjiegu/bridge.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "鐵索橋");
        set("long", @LONG
一座橫跨瀾滄江的鐵索橋，此橋共有四道鐵索，兩條在下，上舖
木板，以供行走，兩條在旁，作為扶手。一踏上橋，幾條鐵索便即晃
動。江水盪盪，如快馬奔騰從腳底飛過，只要一個失足，卷入江水，
任你多好的水性也難活命。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 2 */
            "west" : __DIR__"port2",
            "east" : __DIR__"port",
        ]));

        setup();
}
