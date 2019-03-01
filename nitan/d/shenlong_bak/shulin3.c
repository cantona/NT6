// /d/shenlong/shulin3.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "小樹林");
        set("long", @LONG
這兒是一片小樹林，樹林中間有一小塊空地。空地上除了坑窪
以外還堆了一些不同大小的石塊，這些石塊表面都比較光滑似乎是
人力所為。你一抬頭發現空地四周的樹幹上都沒了樹皮。
LONG );

        set("exits", ([
                "southeast" : __DIR__"luanshi",
        ]));
        set("outdoors", "shenlong");
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_kick", "kick");
        add_action("do_kick", "ti");
        add_action("do_pick", "take");
        add_action("do_pick", "pick");
}

int do_pick(string arg)
{
        object me = this_player();

        if( !arg || !(arg == "shikuai" || arg == "shitou") )
                return notify_fail("什麼？\n");

        if( query_temp("sg/leg", me)>1 )
                return notify_fail("你腿上綁不下那麼多石塊。\n");

        addn("qi", 200/(1+me->query_str()), me);
        if( random(query_temp("sg/shikuai", me))<3 )
        {
                message_vision("$N撿起一塊石頭，掂了掂份量，搖了搖頭，便扔在地上。\n", me);
                addn_temp("sg/shikuai", 1, me);
                return 1;
        }
        delete_temp("sg/shikuai", me);
        if( !query_temp("sg/leg", me) )
        {
                message_vision("$N撿起一塊石頭，掂了掂份量，便把它綁在右腿上。\n", me);
                addn_temp("sg/leg", 1, me);
                addn_temp("apply/dodge", -10, me);
                return 1;
        }
        if( query_temp("sg/leg", me)>0 )
        {
                message_vision("$N撿起一塊石頭，掂了掂份量，便把它綁在左腿上。\n", me);
                addn_temp("apply/dodge", -10, me);
                addn_temp("sg/leg", 1, me);
        }
        return 1;
}

int do_kick(string arg)
{
        object me = this_player();

        if( !arg || !(arg == "tree" || arg == "shu") )
                return notify_fail("什麼？\n");

        message_vision("$N騰空而起雙腿踢向周圍樹幹。\n", me);

        me->receive_damage("jing", 15, "心力絞瘁死了");
        me->receive_damage("qi", 25, "力盡而死");
//        me->improve_skill("kick", random(me->query_int()));

        if( query_temp("sg/leg", me) == 2 )
        {
                me->receive_damage("jing", 10, "心力絞瘁死了");
                me->receive_damage("qi", 20, "力盡而死");
                me->improve_skill("dodge", random(me->query_int()));
                return 1;
        }
        if( query_temp("sg/leg", me) == 1 )
        {
                me->receive_damage("jing", 8, "心力絞瘁死了");
                me->receive_damage("qi", 16, "力盡而死");
                me->improve_skill("dodge", random(me->query_int() / 2));
                return 1;
        }
        me->improve_skill("dodge", random(me->query_int() / 5));
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query_temp("sg/leg", me) )
        {
                addn_temp("apply/dodge",query_temp("sg/leg",  me)*10, me);
                message_vision("$N鬆了綁，將腿上的石塊扔在一邊。\n", me);
                delete_temp("sg/leg", me);
                me->start_busy(1);
        }

        return ::valid_leave(me, dir);
}

