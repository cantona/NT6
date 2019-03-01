inherit ROOM;
#include <ansi.h>

string look_duilian();
string look_bian();

void create()
{
        set("short", "書房大門");
        set("long", @LONG
這是書房門口，只見大門旁貼著副對聯 (duilian)，抬頭上望。
門楣上一塊大匾(bian)上寫著幾個大字。
LONG );
        set("outdoors", "lingjiu");
        set("exits", ([
                "east" : __DIR__"shufang",
                "west" : __DIR__"changl12",
        ]));
        set("objects",([
                CLASS_D("lingjiu") + "/zhujian" : 1,
        ]));
        set("item_desc", ([
                "duilian" :       (: look_duilian :),
                "bian"    :       (: look_bian :),
        ]));
        setup();
}

string look_duilian()
{
        return
        HIR "\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "　行　" NOR + HIR "※※            ※※" NOR + HIW "  坐  " NOR + HIR "※※\n"
        "             ※※　 　 ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  到  " NOR + HIR "※※            ※※" NOR + HIW "  看  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  水  " NOR + HIR "※※            ※※" NOR + HIW "  雲  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  窮  " NOR + HIR "※※            ※※" NOR + HIW "  起  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  處  " NOR + HIR "※※            ※※" NOR + HIW "  時  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※※※※※※            ※※※※※※※\n\n" NOR;
}

string look_bian()
{
    return
    "\n"
              HIY "               ####################################\n"
                  "               ####                            ####\n"
                  "               ####    任    我    逍    遙    ####\n"  
                  "               ####                            ####\n"
                  "               ####################################\n\n\n\n\n\n\n" NOR;
    "\n";
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir != "east")
                return 1;

        if (objectp(guarder = present("zhu jian", environment(me))))
                return guarder->permit_pass(me, dir);

        return 1;
}