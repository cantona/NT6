// /d/shenlong/luanshi.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "亂石");
        set("long", @LONG
這兒是亂石堆，似乎不是天然而成。一陣海風吹來，你打了一個哆
嗦，不禁害怕起來，但細想一下不知其所以然。
LONG
        );

        set("outdoors", "shenlong");
        set("exits", ([
              "southup"   : __DIR__"houshan",
              "northeast" : __DIR__"jushi",
        ]));

        set("no_clean_up", 0);
        setup();
}

void init()
{
        object me = this_player();
        int damage;

        if( interactive(me = this_player()) &&
                !(query("sg/spy", me) || 
                query("family/family_name", me) == "神龍教") && 
                random((int)me->query_skill("dodge")) < 80 )
        {
                message_vision( HIR "$N的眼前突然出現一個無底的深淵...$N掉入了陷阱之中。\n" NOR, me);
                message_vision( HIR"陷阱中的鋼板突然冒出許多鋒利的鋼針，深深地紮進$N的身體中...\n" NOR, me);
                damage = 100000 / ( 100 + (int)me->query_skill("force"));
                me->receive_wound("qi", damage + random(damage), "被紮死了");
                me->receive_damage("qi", damage + random(damage), "被紮死了");

                me->apply_condition("snake_poison", 50 + random(50) + me->query_condition("snake_poison"));
        }
}
