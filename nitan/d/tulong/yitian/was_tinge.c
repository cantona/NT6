#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "側廳");
        set("long", @LONG
這裡是萬安寺的側廳，地上擺著幾個蒲團。
LONG );
        set("exits", ([
                "west" : "/d/tulong/yitian/was_zoulang1",
        ]));

        set("outdoors", "beijing");
        setup();
}

