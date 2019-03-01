// yuanshidian.c 元始殿
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "元始殿");
        set("long", @LONG
這裏是供奉元始天尊的大殿。殿內香煙繚繞，正中央塑着元始天
尊的金身，旁邊還塑着幾位道友如太乙、俱留孫、雲中子、廣和子等
等的像，正聚在一處或躺或坐，或棋或茶。
LONG
        );
        set("exits", ([
                "south" : __DIR__"laojundian",
        ]));
        set("objects", ([
                CLASS_D("quanzhen")+"/qi" : 1,
        ] ));

        set("coor/x", -2770);
        set("coor/y", 120);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}