#include <ansi.h>
inherit ROOM;

string look_duilian();

void create()
{
        set("short", "福嚴寺");
        set("long", @LONG
福嚴寺為禪宗七祖懷讓的道場，懷讓曾在此宏揚頓悟法門。山門
的上匾額「[1；31m天下法院[2；37；0m」正是當年寫照，兩邊門聯「[1；37m六朝古剎  七祖道
場[2；37；0m」字跡剝落顏色極古。只見山門的牆邊上有古人留字(zi)，年代古
遠，猶歷歷可辯。福嚴寺內的石柱上有一對聯(lian)，字跡圓潤回轉，
不露機鋒。
LONG );
        set("exits", ([ 
                "southdown"  : __DIR__"shanlu9",
                "westup"     : __DIR__"sansheng",         
        ]));

        set("objects", ([
                __DIR__"npc/xiangke" : 2,
        ]));        

        set("item_desc", ([
            "zi":
HIW"\n
          諸峰翠少中峰翠  五寺名高此寺名
          石路險盤嵐靄滑  僧窗高倚濟寥明
          凌空殿閣由天設  遍地鬆杉是自生
          更有上方難上處  紫苔紅蘚遠崢嶸
\n\n"NOR,
            "lian" : (: look_duilian :),

        ]));

        set("no_clean_up", 0);

	set("coor/x", -6940);
	set("coor/y", -5570);
	set("coor/z", 0);
	setup();
}


string look_duilian()
{
        return
        HIR "\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "　福　" NOR + HIR "※※            ※※" NOR + HIW "  般  " NOR + HIR "※※\n"
        "             ※※　 　 ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  嚴  " NOR + HIR "※※            ※※" NOR + HIW "  若  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  為  " NOR + HIR "※※            ※※" NOR + HIW "  為  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  南  " NOR + HIR "※※            ※※" NOR + HIW "  老  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  山  " NOR + HIR "※※            ※※" NOR + HIW "  祖  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  第  " NOR + HIR "※※            ※※" NOR + HIW "  不  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  一  " NOR + HIR "※※            ※※" NOR + HIW "  二  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  古  " NOR + HIR "※※            ※※" NOR + HIW "  法  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  剎  " NOR + HIR "※※            ※※" NOR + HIW "  門  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※※※※※※            ※※※※※※※\n\n" NOR;
}
