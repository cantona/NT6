#include <ansi.h>
inherit ROOM;
void create()
{ 
        set("short","秘室");
        set("long", @LONG
這裡是明教秘道裡的一間小小的秘室。
LONG );
    
        set("exits", ([
                  "down" : __DIR__"midao12",
        ]));             
        set("objects",([
                CLASS_D("mingjiao") + "/cheng" : 1,
        ]));
        setup();
}
