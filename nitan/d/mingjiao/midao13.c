#include <ansi.h>
inherit ROOM;
void create()
{ 
        set("short","祕室");
        set("long", @LONG
這裏是明教祕道里的一間小小的祕室。
LONG );
    
        set("exits", ([
                  "down" : __DIR__"midao12",
        ]));             
        set("objects",([
                CLASS_D("mingjiao") + "/cheng" : 1,
        ]));
        setup();
}
