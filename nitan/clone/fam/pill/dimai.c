#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "地脈血泉" NOR, ({ "dimai xuequan", "dimai", "xuequan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", HIM "這是一塊散發著血色光澤的晶體，世間罕有。\n" NOR);
                set("value", 30000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        string mapsk;
        int na, un;
        mapping my = me->query_entire_dbase();

        na = query("name");
        un = query("unit");

        if ((int)me->query_condition("pill_drug") > 0)
        {
                write("你覺得現在內息未定，經脈隱隱還能感到真氣沖盪，不"
                      "敢貿然服食。\n");
                return 1;
        }

        me->apply_condition("pill_drug", 4000);

        message_vision(HIY "$N" HIY "吞下一" + un + na + HIY "，臉色一變，似"
                       "乎精神了許多。\n" NOR, me);

        mapsk = me->query_skill_mapped("force");

        if (me->can_improve_skill("force")
           || (stringp(mapsk) && me->can_improve_skill(mapsk)))
        {
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 20000);

                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 20000);

                tell_object(me, HIR "你只覺一股暖氣散布全身，說不出的舒服受用。\n" NOR);
        } else
                tell_object(me, HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);

        me->improve_neili(100 + random(101));

        if( query("neili", me)<query("max_neili", me) )
                my["neili"]  = my["max_neili"];

        me->start_busy(random(8) + 8);
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
