// Room: /d/mobei/caoyuan6.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set ("short", "鐵木真部落");
        set ("long", @LONG
鐵木真部落是當今蒙古草原上最強盛的一族，由于他有勇有謀，善
于用人，草原上的英雄都願意為他效力，你目光所到之處，牛肥馬壯，
連綿的蒙古包遮蓋了舉目所見的整的草原。
LONG);
        set("no_clean_up", 0);
        set("outdoors","mobei");
        set("exits", ([ /* sizeof() == 3 */
                "northeast" : __DIR__"buluo",
                "southwest" : __DIR__"caoyuan5",
                "west"      : __DIR__"shulin1",
        ]));
        set("coor/x", -220);
        set("coor/y", 5200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}