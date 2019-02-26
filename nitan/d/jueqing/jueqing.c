#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "絕情峯");
        set("long", @LONG
這裏便是絕情谷絕頂之處絕情峯，矗立此處俯瞰羣峯，但
見羣峯間雲霧繚繞，輕煙縷縷。峯下千溝萬壑，樹木叢生，刺
骨的山風吹過，令人感到陣陣寒意。
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "southdown" : __DIR__"shanlu8",
        ]));

        set("no_clean_up", 0);
        
        setup();
        replace_program(ROOM);
}
