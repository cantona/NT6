// Room: /d/xingxiu/xiaolu.c
// Last Modified by winder on Apr. 25 2001

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "小路");
        set("long", @LONG
你走在一條在星宿海海邊亂石堆裡崎嶇的小路上，路邊有一群星宿
弟子正在長嘯練功。這裡，陰風凜冽，西面是望浩浩百裡方圓的星宿海。
東面是座陡峭之極的山壁，壁上有一凸出的巨石(jushi) 。
LONG);
        set("exits", ([
                "west"    : __DIR__"xxh2",
                "northup" : __DIR__"shanbi",
        ]));
        set("item_desc", ([
                "jushi" : "一數米高的黑褐色巨石。\n"
        ]));
        set("objects", ([
                CLASS_D("xingxiu")+"/tianlang"  : 1,
                __DIR__"npc/xxdizi" : 1,
        ]));
        set("coor/x", -49900);
        set("coor/y", 20200);
        set("coor/z", 0);
        set("outdoors", "xingxiu");
        setup();
}

void init()
{
        add_action("do_pa", "pa");
        add_action("do_pa", "climb");
}

int do_pa(string arg)
{
        object me = this_player();
        mapping myfam;
        myfam=query("family", me);

        if( !arg || arg=="" ) return 0;
        if( arg=="jushi" )
        {
                if ((!myfam || myfam["family_name"] != "星宿派") &&
                        (present("tianlang zi", environment(me)))) 
                        return notify_fail("天狼子閃身攔在你面前, 喝道：不想死的就快滾開！\n");
                if(me->query_skill("dodge") < 100)
                        return notify_fail("你想爬上巨石，怎奈身法不夠上不去。\n");       
                message_vision("$N很費勁地爬上巨石。\n", me);
                message("vision", me->name() + "一轉眼便消失在山壁上。\n", environment(me), ({me}) );
                if( time()-query_temp("LAST_PKER_TIME", me)<7200 )
                {
                        write( WHT"你爬上巨石，卻發現上面已無容身之處，只好悻悻的退了下來。\n"NOR );
                        me->move( __DIR__"xiaolu" );
                        return 1;
                }
                me->move(__DIR__"jushi");
                message("vision", me->name() + "從山壁下爬了上來。\n", environment(me), ({me}) );
                return 1;
        }
}
