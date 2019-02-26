#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIY"可汗帳營"NOR);
        set("long", @LONG
這裏就是「蒙古」可汗的帳營，兩邊分立着眾將領軍士，蒙古可
汗親自領兵南征，在這裏商討謀劃進軍的策略，帳外不時傳來軍馬的
嘶鳴聲，那是蒙古騎兵在進行操練，看來這次南征的準備已非一日。
LONG );
        set("no_cleanup",1);

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"mying",
               "north" :   __DIR__"mying4",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
