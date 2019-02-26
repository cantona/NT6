// qiankun-except.c

#include <ansi.h>

inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
        int n;

        if (me != ob)
        {
                tell_object(ob, "你發覺" + me->name() + "的內力自奇經八脈湧入，一時"
                            "間丹田之中內息交戰，眼前登時一黑。\n");
                tell_object(me, "你試圖幫助" + ob->name() + "化解異種真氣，"
                            "卻見" + ob->name() + "臉色慘白，不由大驚，連忙住手。\n");
                if (living(ob)) ob->unconcious();
                return -1;
        }

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
        {
                tell_object(me, HIW "你只覺得丹田猶如寒冰，一運內力"
                            "就覺得如同千百根鋼針一齊攢刺。\n" NOR);
                return -1;
        }

        if (me->query_skill("jiuyang-shengong", 1) + 30 < duration)
        {
                tell_object(me, "你試圖運用九陽神功化解這股"
                            "陰寒之氣，但是總是功虧一簣。\n");
                return -1;
        }

        n = me->query_condition("qiankun-except") -
            (int)me->query_skill("jiuyang-shengong", 1) / 10;
        if (n < 1)
                me->clear_condition("qiankun-except");
        else
                me->apply_condition("qiankun-except", n);

        tell_object(me, "你默默的運用九陽神功化解體內的異種真氣。\n");

        return 1;
}

int update_condition(object me, int duration)
{
        int limit;

        if (! living(me) && (me->query("eff_qi") < 100 || me->query("eff_jing") < 50))
        {
                me->set_temp("die_reason", "因為強自修煉乾坤大挪移神功，走火入魔而死");
                me->die();
                return 0;
        } else
        {
                me->receive_wound("qi", 100);
                me->receive_wound("jing", 50);
                tell_object(me, HIR "你覺得丹田陣陣寒冷，可是臉上卻"
                            "好像發燒一樣火熱之極。\n" NOR);
                message("vision", me->name() + "臉色忽青忽紅，強忍着運功抗爭。\n",
                        environment(me), me);
        }

        return 1;
}
