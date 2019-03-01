#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "絕情峰");
        set("long", @LONG
這裡便是絕情谷絕頂之處絕情峰，矗立此處俯瞰群峰，但
見群峰間雲霧繚繞，輕煙縷縷。峰下千溝萬壑，樹木叢生，刺
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
