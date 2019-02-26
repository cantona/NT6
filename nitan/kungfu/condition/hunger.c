// hunger.c

#include <condition.h>
#include <ansi.h>

int dispel() { return 0; }

int update_condition(object me, int duration)
{
        if (me->query("food") > 0 && me->query("water") > 0)
                return 0;

        if (! interactive(me) ||
            ! environment(me) ||
            environment(me)->is_chat_room())
                return CND_CONTINUE;

        if (duration == 4)
        {
                if (me->query("food") <= 0 && me->query("water") <= 0)
                        tell_object(me, HIY "你餓得頭暈眼花，渴得喉嚨冒煙，看來"
                                    "要趕快找點吃喝的東西了。\n"NOR);
                else
                if (me->query("food") <= 0)
                        tell_object(me, HIY "你餓得頭暈眼花，看來要趕快找點吃的了。\n" NOR);
                else
                if (me->query("water") <= 0)
                        tell_object(me, HIY "\n你渴得喉嚨冒煙，看來要趕快喝點什麼了。\n" NOR);
        }
        else
        if (duration == 7)
        {
                if (me->query("food") <= 0 && me->query("water") <= 0)
                        tell_object(me, HIR "你又飢又渴，覺得自己快要死了。\n"NOR);
                else
                if (me->query("food") <= 0)
                        tell_object(me, HIR "你餓得快死了。\n"NOR);
                else
                if (me->query("water") <= 0)
                        tell_object(me, HIR "你渴得要虛脱了。\n"NOR);
        }
        else
        if (duration >= 13)
        {
                if (wizardp(me))
                {
                        tell_object(me, HIY "你眼看快要餓死了，好在你是巫師，變！"
                                        "變！變！你三口兩口把變出來\n" +
                                        "的不知道什麼東西給吞下肚，感覺好多了。\n" NOR);
                        me->set("food", me->max_food_capacity());
                        me->set("water", me->max_food_capacity());
                        return 0;
                }

                if (me->query("mud_age") < 86400)
                {
                        tell_object(me, HIY "你眼看就要不行了，突然天下掉下餡餅牛"
                                        "奶，你一陣狂吃濫喝，感覺總\n" +
                                        "算是好多了。\n" NOR);
                        me->set("food", me->max_food_capacity());
                        me->set("water", me->max_food_capacity());
                        return 0;
                }

                if (me->query("food") <= 0 && me->query("water") == 0)
                        tell_object(me, HIR "你又飢又渴，終於暈了過去。\n"NOR);
                else
                if (me->query("food") <= 0)
                        tell_object(me, HIR "你餓得暈了過去。\n"NOR);
                else
                if (me->query("water") <= 0)
                        tell_object(me, HIR "你渴得暈了過去。\n"NOR);
                me->receive_damage("qi", 0);
                me->unconcious();
                return 0;
        }
        
        me->apply_condition("hunger", duration + 1);
        return CND_CONTINUE;
}
