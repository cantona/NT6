// Room: /d/hengshan/huixiantai.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "見性峯廣場");
        set("long", @LONG
這裏是恆山主峯見性峯峯頂的廣場。在這裏俯瞰羣山，才理會得何
以恆山是華夏北方萬山之宗，這裏也是威震江湖的恆山派的根本重地。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "westdown"  : __DIR__"shandao2",
                "north"     : __DIR__"baiyunan",
        ]));
        set("objects", ([
                CLASS_D("hengshan")+"/yi" : 1,
                CLASS_D("hengshan")+"/qing" : 1,
                CLASS_D("hengshan")+"/first" : 1,
        ]));
        
        set("outdoors", "hengshan");
//        set("no_clean_up", 0);
        set("coor/x", 40);
        set("coor/y", 3200);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}
