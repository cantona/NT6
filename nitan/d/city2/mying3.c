#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"突騎營"NOR);
        set("long", @LONG
這裡就是「蒙古」突騎軍大營，營內軍馬嘶鳴，塵土飛揚，蒙古
軍為了南征，早已調派了最精銳的蒙古騎兵，看見蒙古軍迅疾如風的
沖鋒陣列，不由不讓人心驚膽寒。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "east"  :   __DIR__"mying4",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
