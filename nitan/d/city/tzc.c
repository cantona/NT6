#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY+BLINK"挑戰擂台"NOR);
        set("long", @LONG
[1；36m這裏是專門設來接受外國挑戰的擂台。
LONG );
        set("no_drift", 1);
        set("no_clean_up", 0);
        set("exits",([
                "down" : "/d/city/guangchang",
        ]));

        setup();
        replace_program(ROOM);
}
