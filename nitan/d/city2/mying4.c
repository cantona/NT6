#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"弓兵營"NOR);
        set("long", @LONG
這裡就是「蒙古」弓兵訓練大營，蒙古軍歷來以弓馬之利而揚名，
因此蒙古軍中的神箭手更是屢見不鮮，這次南征，蒙古可汗特地加調
了一匹精銳蒙古弓箭手協助作戰，難怪蒙古可汗大有勢在必得之架勢。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "north" :   __DIR__"myuanmen2",
               "south" :   __DIR__"mying1",
               "west"  :   __DIR__"mying3",
               "east"  :   __DIR__"mying2",     
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
