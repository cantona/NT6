inherit ROOM;
string look_duilian();

#include <ansi.h>;

void create()
{
        set("short", "凌霄殿");
        set("long", 
"這裏就是凌霄城的根本之地--凌霄殿。向來，不管凌霄城有
何大事，掌門都會在此召集門人，發號施令。大廳北牆上，掛着
一個老人的肖像，是當年凌霄城創派祖師的遺像。兩邊柱子上刻
着一幅對聯(duilian)。旁邊的兵器架上放滿了寒光閃閃的長劍。
堂額掛着一張匾，上書四個大字。" HIW "

                  梅    雪    凌    霄
\n" NOR );
        set("item_desc",([
                "duilian"         :       (: look_duilian :),
        ]));
        set("exits", ([
                "east"  : __DIR__"fudian2",
                "west"  : __DIR__"fudian1",
                "north"  : __DIR__"qianyuan",
                "south"  : __DIR__"meiroad1",
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/luwantong" : 1,
                __DIR__"npc/dizi" : 4,
        ]));
        set("no_clean_up", 0);
        set("valid_startroom", 1);
        setup();
        "/clone/board/lingxiao_b"->foo();
} 

string look_duilian()
{
        return
        HIR "\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "　寶　" NOR + HIR "※※            ※※" NOR + HIW "  梅  " NOR + HIR "※※\n"
        "             ※※　 　 ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  劍  " NOR + HIR "※※            ※※" NOR + HIW "  花  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  鋒  " NOR + HIR "※※            ※※" NOR + HIW "  香  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  自  " NOR + HIR "※※            ※※" NOR + HIW "  自  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  磨  " NOR + HIR "※※            ※※" NOR + HIW "  苦  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  礪  " NOR + HIR "※※            ※※" NOR + HIW "  寒  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  出  " NOR + HIR "※※            ※※" NOR + HIW "  來  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※※※※※※            ※※※※※※※\n\n" NOR;
}

int valid_leave(object me, string dir)
{
        object lu;

        if (dir != "east" &&
            dir != "west" &&
            dir != "north" ||
            ! objectp(lu = present("lu wantong", this_object())))
                return ::valid_leave(me, dir);

        return lu->permit_pass(me, dir);
}