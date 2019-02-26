#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR "【輪迴司】" NOR);
        set("long", HIR @LONG

                 輪        回        司

    這裏陰陽交匯之處，周圍一片黑暗，只有一陣陣氤氲之氣從下方湧出。

LONG NOR );

        set("sleep_room", 1);

        set("sky", 1);
        // 在此演練lunhui-sword
        set("lunhui", 1);
        set("valid_startroom", 1);
        setup();
}
