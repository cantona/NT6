// xixing-fanshi.c

#include <ansi.h>

inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
        int n;

        if (me != ob)
        {
                tell_object(ob, "你發覺" + me->name() + "的內力源源湧進，原"
                            "本紊亂的內息更是厲害，眼前登時一黑。\n");
                tell_object(me, "你試圖幫助" + ob->name() + "化解異種真氣，"
                            "卻忽然發現自己的內力源源而逝，不由大驚，連忙住手。\n");
                if (living(ob)) ob->unconcious();
                return -1;
        }

        if (me->query_skill_mapped("force") != "yijinjing")
        {
                tell_object(me, "你覺得異種真氣左突右沖，內息"
                            "大亂，根本無法將內力凝聚起來。\n");
                return -1;
        }

        n = me->query_condition("xixing-fanshi") -
            (int)me->query_skill("yijinjing", 1) / 10;
        if (n < 1)
                me->clear_condition("xixing-fanshi");
        else
                me->apply_condition("xixing-fanshi", n);

        tell_object(me, "你默默的運用易筋經神功化解體內的異種真氣。\n");

        return 1;
}

int update_condition(object me, int duration)
{
        int limit;

        if (! living(me) && (me->query("eff_qi") < 20 || me->query("eff_jing") < 10))
        {
                me->set_temp("因為修習吸星大法不慎，內力反噬吐血身亡了");
                me->die();
                return 0;
        } else
        {
                me->receive_wound("qi", 20);
                me->receive_wound("jing", 10);
                if (me->query("max_neili"))
                        me->add("max_neili", -1);
                tell_object(me, HIR "你覺得丹田內息紊亂之極，渾身忽冷忽"
                                "熱，四肢百賅內力激盪，幾欲暈厥。\n" NOR);
                message("vision", me->name() + "臉色忽青忽紅，四肢不住的顫動。\n",
                        environment(me), me);
        }

        if (me->query("max_neili") < 1)
                duration = 1;
        me->apply_condition("xixing-fanshi", duration - 1);
        if (! duration) return 0;
        return 1;
}
