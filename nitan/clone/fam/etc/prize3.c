#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "赤龍之瞳" NOR, ({ "dragon eye", "dragon", "eye" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "傳説中赤龍的眼珠，似乎可以服用。\n" NOR);
                set("unit", "顆");
                set("value", 500000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        string mapsk;
        string na, un;
        mapping my = me->query_entire_dbase();

        na = query("name");
        un = query("unit");

        if ((int)me->query_condition("pill_drug") > 0)
        {
                write("你覺得現在內息未定，經脈隱隱還能感到真"
                      "氣衝蕩，不敢貿然服食。\n");
                return 1;
        }

        me->apply_condition("pill_drug", 300);

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

                tell_object(me, HIM "你只覺一股暖氣散佈全身，説不出的舒服受用。\n" NOR);
        } else
                tell_object(me, HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);

        if( query("neili", me)<query("max_neili", me) )
                my["neili"]  = my["max_neili"];

        me->start_busy(random(3) + 3);
        destruct(this_object());
        return 1;
}