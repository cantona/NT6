// cundaota1.c 存道塔一層
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "存道塔一層");
        set("long", @LONG
這裡是存道塔的一層，存道塔是當年全真弟子用來存放經書的地
方，塔不高，是用一塊一塊的大青石砌起來的。塔中的梯子也是用青
石所砌，據說之所以用石頭砌塔是為了避免失火，燒毀了全真教的經
書。
LONG
        );
        set("exits", ([
                "south" : __DIR__"guozhendian",
                "westup" : __DIR__"cundaota2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2780);
        set("coor/y", 130);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}