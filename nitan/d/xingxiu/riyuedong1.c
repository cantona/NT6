// Room: /d/xingxiu/riyuedong1.c
// Last Modified by winder on Apr. 25 2001
#include <ansi.h>

string look_duilian();
inherit ROOM;
void create()
{
        set("short", "日月洞口");
        set("long", @LONG
這裡是星宿海的盡頭。說是海，其實是片湖泊和沼澤，地形十分險
惡。方圓幾百裡都是一望無際的湖泊和沼澤，當地牧羊人就稱之為“海
”。這裡左右兩廂通向星宿海的深處，北邊是一座小石山，星宿派總舵
日月洞便設在這裡，洞口立著一個銅制牌子(paizi)。
LONG);
        set("exits", ([
                "north"     : __DIR__"riyuedong",
                //"west"      : __DIR__"xxh4",
                //"east"      : __DIR__"xxh3",
                "northwest" : __DIR__"xxhb2",
                "northeast" : __DIR__"xxhb1",
                "southdown" : __DIR__"huangdi",
        ]));
        set("item_desc", ([
                "paizi" : (: look_duilian :),
        ]));
        set("objects", ([
                CLASS_D("xingxiu")+"/anran" : 1,
                CLASS_D("xingxiu")+"/first" : 1,
                //CLASS_D("xingxiu")+"/first" : 1,
                __DIR__"npc/gushou" : 1,
                __DIR__"npc/haoshou" : 1,
                __DIR__"npc/boshou" : 1,
        ]) );
        set("valid_startroom","1");
        set("coor/x", -50000);
        set("coor/y", 20300);
        set("coor/z", 100);
        set("outdoors", "xingxiu");
        setup();
        "/clone/board/xingxiu_b"->foo();
        //replace_program(ROOM);
}

string look_duilian()
{
        return
        RED "\n"
        "        ※※※※※※※            ※※※※※※※\n"
        "        ※※※※※※※            ※※※※※※※\n"
        "        ※※      ※※            ※※      ※※\n"
        "        ※※" NOR + HIW "　星　" NOR + RED "※※            ※※" NOR + HIW "  日  " NOR + RED "※※\n"
        "        ※※　 　 ※※            ※※      ※※\n"
        "        ※※" NOR + HIW "  宿  " NOR + RED "※※            ※※" NOR + HIW "  月  " NOR + RED "※※\n"
        "        ※※      ※※            ※※      ※※\n"
        "        ※※" NOR + HIW "  海  " NOR + RED "※※            ※※" NOR + HIW "  洞  " NOR + RED "※※\n"
        "        ※※      ※※            ※※      ※※\n"
        "        ※※" NOR + HIW "  福  " NOR + RED "※※            ※※" NOR + HIW "  洞  " NOR + RED "※※\n"
        "        ※※      ※※            ※※      ※※\n"
        "        ※※" NOR + HIW "  地  " NOR + RED "※※            ※※" NOR + HIW "  天  " NOR + RED "※※\n"
        "        ※※    　※※            ※※      ※※\n"
        "        ※※※※※※※            ※※※※※※※\n"
        "        ※※※※※※※            ※※※※※※※\n\n\n" NOR;
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (! objectp(guarder = present("anran zi", this_object())))
                return 1;

        if (dir == "north")
                return guarder->permit_pass(me, dir);


        return 1;
}
