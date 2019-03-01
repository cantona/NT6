// flower_poison.c

#include <ansi.h>

int dispel(object me, object ob)
{
        if (me == ob)
        {
                tell_object(me, "你試圖運功化解斷腸花毒，突然一感到"
                                "陣撕心裂肺的疼痛，幾乎暈厥。\n");
                return -1;
        }

        tell_object(me, "你將真氣輸入" + ob->name() + "體中，卻覺得"
                        "真氣運轉異常怪異，難以理解，\n突然見" + ob->name() +
                        "汗如雨下，連忙住手。\n");
        tell_object(ob, "你覺得" + me->name() + "將內力緩緩輸入你的"
                        "經脈，忽然一陣撕心裂肺的劇痛，\n猶勝斷腸花"
                        "毒發作的時候，令你幾乎暈厥。\n");
        return -1;
}

int update_condition(object me, int duration)
{
        if(me->query_temp("nopoison")) return 0;

        message("vision", HIG + me->name() + "一陣搖晃，立足"
                          "不定。\n" NOR,
                environment(me), me);

        if(! living(me) &&
           (me->query("qi") < 25 || me->query("jing") < 25))
        {
                      me->set_temp("die_reason", "斷腸花毒發作，不治身亡了");
                      me->die();
                      return 0;
        }

        me->receive_wound("jing", 25 + random(25));
        me->receive_damage("jing", 25 + random(25));
        me->receive_wound("qi", 50 + random(50));
        me->receive_damage("qi", 50 + random(50));
        if (me->query_skill("force") >= 300)
                me->apply_condition("flower_poison", duration - 1);
        tell_object(me, HIG "你中的" HIR "斷腸花毒" HIG "發作了！\n" NOR );
        if( duration < 1 )
        {
                tell_object(me, HIR "你心口一陣劇痛，不禁一陣暈眩，過"
                            "後感覺卻好了一些。\n" NOR);
                return 0;
        }
        return 1;
}

