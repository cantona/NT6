#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "【碧水寒潭】" NOR);
        set("long", HIB @LONG

                    碧     水     寒     潭

    這裡便是陰司的碧水寒潭，傳說四神獸之首的青龍常常出沒于此潭
中。潭中冰水中幽暗無比，四周似乎有幾處出口，但實在看不清是通向
何處。水中冰冷刺骨，令人難以忍受，你只覺得氣力在一點一點消失。


LONG NOR );

        set("exits", ([
                "east" : __DIR__"hantan8",
                "west" : __DIR__"hantan3",
                "south" :__DIR__"hantan2",
                "north" :__DIR__"hantan6",
        ]));
        set("no_clean_up", 0);
        set("no_magic", 1);
        set("is_hantan", 1); 

        setup();
}

void init()
{
        object me;
        int meqi, meneili, decqi, mq;
        me = this_player();

        if ( present("diyin xuemai", me))
        {
                tell_object(me, RED "你懷中的地陰血脈發出一陣陣熱量，護住了周身的"
                                "經脈！\n" NOR);
                return 0;
        }
        tell_object(me, HIW "你身陷碧水寒潭，潭中寒冰削肉刮骨，你"
                        "只覺渾身血液都被凍住一般！\n" NOR);
        meqi=query("qi", me);
        meneili=query("neili", me);
        mq=query("max_qi", me);
        decqi = (int)( mq / (random(4) + 5 + meneili/200) );
        meqi = meqi - decqi;
        set("neili", 0, me);

        if(meqi > 0)
        {
                set("qi", meqi, me);
        }
   else {
                set_temp("die_reason", "在碧水寒潭給活活凍死了", me);
                me->die();
        }
        return 0;
}