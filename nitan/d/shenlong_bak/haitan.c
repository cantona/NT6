//  /d/shenlong/haitan.c 海灘
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "海灘");
        set("long", @LONG
但見岸上樹木蒼翠，長長的海灘望不到盡頭，盡是雪白的細沙，四
處一片寂靜，聽不見一點聲音，西面是大海，東面仿拂有一座山峰，兩
旁是望不到盡頭的海灘。島上的空氣似乎又熱又悶，咸濕的海風中帶著
一股腥臭，又夾雜了一縷奇特的花香，聞起來十分怪異。
LONG
        );
        set("exits", ([
                "east"  : __DIR__"shanlu1",
                "west"  : __DIR__"beach",
                "south" :__DIR__"jiutou1.1", 
                "southeast"  :__DIR__"jiutou3/jiutou1.2", 
                "southwest"  :__DIR__"jiutou4/jiutou1.2", 
                "northwest"  :__DIR__"jiutou11/jiutou1.2", 
                "northeast"  :__DIR__"jiutou22/jiutou1.4", 
                "north" : __DIR__"lin1",
        ]));
        set("outdoors", "shenlong");

        setup();
}

void init()
{
        object me = this_player();
        int damage;

        set("startroom", base_name(this_object()), me);
        me->save();
        if( interactive(me = this_player()) &&
                !(query("sg/spy", me) || 
                query("family/family_name", me) == "神龍教") && 
                random((int)me->query_skill("dodge")) < 80 )
        {
                message_vision( HIR "$N的眼前突然出現一個無底的深淵...$N掉入了陷阱之中。\n" NOR, me);
                message_vision( HIR "陷阱中的鋼板突然冒出許多鋒利的鋼針，深深地紮入了$N的身體中...\n" NOR, me);
                damage = 100000 / ( 100 + (int)me->query_skill("force"));
                me->receive_wound("qi", damage + random(damage), "被紮死了");
                me->receive_damage("qi", damage + random(damage), "被紮死了");
                me->apply_condition("snake_poison", 50 + random(50) +
                me->query_condition("snake_poison"));
        }
}
