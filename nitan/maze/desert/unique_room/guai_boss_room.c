#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIC"賊盜窩點"NOR);
        set("long",@LONG
好多賊盜啊！
LONG);

        set("maze", 1);
        set("no_clean_up", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("outdoors", "forest");

        set("objects",([
                "/maze/desert/npc/guai_boss": 1,
                "/maze/desert/npc/guai": 3,
        ]));
        setup();
}
