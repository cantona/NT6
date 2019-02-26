// Room: /d/kunlun/kuhanlou3.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;
int do_out(string arg);

void create()
{
        set("short", "苦寒樓三層");
        set("long", @LONG
很快就到了苦寒樓頂層。這裏可以看到山門以及北邊的諸多崑崙山
峯，四周的杉林隨風搖擺，發出“嘩嘩譁”的聲音。山風夾着隱隱寒氣，
遠處的景色單調而蒼涼，你心裏頓時生出一種莫名寂寞的感覺。房間裏
的佈置十分簡單。往外看，有個很大的紅木窗台(out)。
LONG );
        set("exits", ([
                "down" : __DIR__"kuhanlou2",
        ]));
        set("item_desc", ([
                "out" : "你突然有了一種想跳出去的慾望，怎麼也剋制不住。\n",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -119980);
        set("coor/y", 40130);
        set("coor/z", 110);
        setup();
}

void init()
{
        object me = this_player();

        if( (query_temp("count", me) == 2 )
                && (int)me->query_skill("dodge", 1) >= 30
                && (int)me->query_skill("dodge", 1) <= 101)
        {
                me->receive_damage("jing", 30);
                me->improve_skill("dodge",query("int", me));
        }
        me->start_busy(random(3));
        add_action("do_out", "out");
}

int do_out(string arg)
{
        object me;
        int i, jing_cost, qi_cost;

        me = this_player();
        i = (int)me->query_skill("dodge") + random(200);
        jing_cost=600/query("int", me);
        qi_cost=500/query("int", me);
        if( (query("jing", me)<jing_cost) || 
                (query("qi", me)<qi_cost) )
                i = 0;

        message_vision("$N爬上窗台，一個縱身，跳了下去。\n", me);
        me->move(__DIR__"houyuan");
        message_vision("只聽『砰』地一聲$N從樓頂跳了下來。\n", me);
        set_temp("last_damage_from", "從樓上跳下來摔", me);

        if ( i < 60)
                me->die();
        else if( i < 120)
                me->unconcious();
        else {
                message_vision("$N已穩穩地站在地上。\n", me);
                if( i > 250
                        && me->query_skill("dodge", 1) < 120 )
                        me->improve_skill("dodge", 2*(int)me->query_skill("dodge", 1));
                me->receive_damage("jing", jing_cost );
                me->receive_damage("qi", qi_cost );
        }
        return 1;
}