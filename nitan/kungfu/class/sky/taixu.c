#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "【太虛】" NOR);
        set("long", HIW @LONG

                 太              虛

    這裏是三界之外的太虛之中，四周白茫茫的一片，不見任何事物。

LONG NOR );

        set("sleep_room", 1);

        set("sky", 1);
        // 在此演練陰陽九轉十二重天
        set("yinyang", 1);
                set("valid_startroom", 1);
        setup();
}
