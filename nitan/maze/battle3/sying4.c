#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"弓兵營"NOR);
        set("long", @LONG
這裡就是「大宋」弓兵訓練大營，一批批的宋軍神箭手從這裡訓
練產生，讓蒙古軍膽寒，兩軍交鋒，弓箭的使用往往能出奇制勝，因
此大宋也加強了弓箭手的訓練。
LONG );
        set("train", "archer");
        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"syuanmen2",
               "north" :   __DIR__"sying1",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
