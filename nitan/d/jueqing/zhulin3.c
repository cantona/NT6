#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", NOR + GRN "竹林" NOR);
        set("long", @LONG
北方竹子極少，這般大的一片竹林更是罕見。信步穿過竹
林，聞到一陣陣淡淡花香，登覺煩俗盡消。
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "northwest"   : __DIR__"shanlu4",
               "west"        : __DIR__"zhulin2",
               "east"        : __DIR__"danfang",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}