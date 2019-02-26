inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "郭府大門");
	set("long", 
"建築古樸的大宅院出現在你的眼前。只見門樓高挑，門前
立了兩個石獅，大門上書兩個大字" YEL "

              ※※※※※※※※※※※
              ※                  ※
              ※" NOR + HIY "     郭    府" NOR + YEL "     ※
              ※                  ※
              ※※※※※※※※※※※" NOR "

你從大門瞧進去，好像裏面人來人往，都很繁忙的樣子。這裏
站着位青年，神情威嚴。接待前來保衞襄陽的各方義士。
");
        set("outdoors", "wuguan");
	set("exits", ([
		"south" : "/d/xiangyang/westjie1",
		"north" : __DIR__"guofu_dayuan",
	]));
	set("objects", ([
		__DIR__"npc/wudunru" : 1,
                __DIR__"npc/jiading" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
        if( query("mark/guofu_ok", me )
           && present("wu dunru", environment(me)) 
           && dir == "south")
             return notify_fail(CYN "\n武敦儒伸手將你攔住道：現在"
                                "襄陽城內不太平，你還是多呆一會吧"
                                "。\n" NOR);

/*
        if( query("mark/guofu_over", me )
           && present("wu dunru", environment(me))
           && dir == "north")
             return notify_fail(CYN "\n武敦儒將你攔住，冷笑道：郭"
                                "府留你不下，你還是走吧。\n" NOR);

        if( query("mark/guofu_out", me )
           && present("wu dunru", environment(me)) 
           && dir == "north")
             return notify_fail(CYN "\n武敦儒笑道：你再留在郭府已"
                                "無多大的用處，還是多去闖蕩闖蕩吧"
                                "。\n" NOR);

        if( query("combat_exp", me)>5000
            && !query("mark/guofu_ok", me )
           && present("wu dunru", environment(me)) 
           && dir == "north")
             return notify_fail(CYN "\n武敦儒抱拳道：現襄陽正值動"
                                "亂時期，沒師父許可，任何人不得入"
                                "內。\n" NOR);

        if( !query("mark/guofu_ok", me )
           && present("wu dunru", environment(me)) 
           && dir == "north")
             return notify_fail(CYN "\n武敦儒伸手將你攔住道：如果"
                                "你不打算幫忙打雜，就別進來。\n" NOR);
*/

        return ::valid_leave(me, dir);
}
