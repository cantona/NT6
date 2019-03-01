// sheshenya.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "舍身崖");
        set("long", @LONG
這是一段極窄極險的山崖，四周雲霧飛繞，下面淵深無底。如不
小心，一失足掉下去，只怕連骨頭都找不到。邊上有個小山洞(dong)。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "eastdown" : __DIR__"canglong",
        ]));
        set("item_desc", ([
                "dong" : "緊靠飛崖下石壁的小洞，黑呼呼的不知有多深。\n",
        ]));
        set("outdoors", "huashan" );

        setup();
}

void init()
{
        object me = this_player();
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
        if( query_temp("xunshan", me) )
                set_temp("xunshan/sheshen", 1, me);
        return;
}

int do_enter(string arg)
{
        object me;
        mapping fam;

        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( arg=="dong" )
        {
                if( (fam=query("family", me)) && fam["family_name"] == "丐幫" )
                {
                        message("vision",
                                me->name() + "運起丐幫縮骨功，一彎腰往洞裡鑽了進去。",
                                environment(me), ({me}) );
                        me->move("/d/gaibang/undertre");
                        message("vision",
                                me->name() + "從洞裡走了進來。\n",
                                environment(me), ({me}) );
                                return 1;
                } else  
                        return notify_fail("這麼小的洞，你鑽得進去嗎？\n");
        }
}

