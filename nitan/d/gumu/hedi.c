// This program is a part of NT MudLIB

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIR"暗流河底"NOR);
        set("long", @LONG
你沒在水中，感覺似乎是到了水底,水勢已不似剛才那麼迅急，水壓卻是更甚從前。憋得你就要透不過氣來了，你情急
下急急審視四周尋找出路,發覺上方(southup)隱隱透着亮光,不覺
心下一喜,不急細想就欲向上浮去.
LONG
        );

        setup();
}

void init()
{
        object me;

        me = this_player();
        add_action("do_swim","swim");
        me->receive_damage("qi", 500 );
        me->receive_damage("jing", 500 );
        message_vision(HIB"$N的真氣正在流失，呼吸十分困難。\n"NOR, me);
        if( query("qi", me)<10 || query("jing", me)<10 )
        {
                set_temp("die_reason", "在潛流中被淹死", me);
                me->unconcious();
                me->die();
                return ;
        }
}

int do_swim(string arg)
{
        object me;
        me=this_player();

        if ( !arg || arg != "southup" )
                return notify_fail("你要遊向哪裏？\n");

        if ( me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");

        if (arg =="southup")
        {
                if ((int)me->query_encumbrance() * 100 / (int)me->query_max_encumbrance() >= 40)
                        return notify_fail("你身子沉重，用盡全力也無法浮上去!\n");

                message_vision(YEL"$N兩腿用力一蹬，向上面浮去。\n"NOR, me);
                me->receive_damage("jing", 500);
                me->receive_damage("qi", 500);
                me->move(__DIR__"midong");
                tell_room(environment(me), me->name() + "從下面浮了上來。\n", ({ me }));
                message_vision (HIB"$N只覺得頭暈暈的，身體浸在冰冷的水中，不住的顫抖。\n"NOR,me);
                return 1;
        }
        return 1;
}
