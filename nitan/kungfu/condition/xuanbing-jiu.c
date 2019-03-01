// xuanbing-jiu.c
// by vin

#include <ansi.h>
inherit F_CLEAN_UP;

string chinese_name() { return "玄冰碧火酒毒素"; }

int dispel(object me, object ob, int duration)
{
        int f, n, lvl;
        f = me->query_skill_mapped("force");
        lvl = me->query_skill("force");

        if (me != ob)
        {
                tell_object(ob, "你只覺" + me->name() + "的內力使得熱寒兩股真"
                                "氣抗拒得更為激烈，登時眼前一黑。\n");

                tell_object(me, "你試圖幫助" + ob->name() + "解毒，卻發現對方"
                                "熱寒兩股真氣頓生反彈，不由大驚，連忙住手。\n");

                if (living(ob))
                        ob->unconcious();

                return -1;
        }

        if (me->query_skill_mapped("force") != "luohan-fumogong")
        {
                tell_object(me, HIB "你覺得全身忽如" HIW "冰徹" NOR +
                                HIB "，忽如" HIR "火炙" NOR + HIB "。"
                                "全然無法將內息凝聚。\n" NOR);
                return -1;
        }

        if (me->query_skill("luohan-fumogong", 1) < 180)
        {
                tell_object(me, HIB "你發現自身的" + to_chinese(f) +
                                HIB "修為不足，難以將體內的陰陽兩種"
                                "真氣調和。\n");
                return -1;
        }

        n = me->query_condition("xuanbing-jiu") - lvl / 15;

        tell_object(me, "你默默的運用" + to_chinese(f) + "化解體內"
                        "的異種真氣。\n");

        if (n < 1)
        {
                me->clear_condition("xuanbing-jiu");

                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 3000);

                if (me->can_improve_skill("luohan-fumogong"))
                        me->improve_skill("luohan-fumogong", 3000);

                if( me->addn("can_perform/luohan-fumogong/jiu",1+random(5))<100 )
                {
                        tell_object(me, HIC "\n突然間你發覺體內陰陽兩種真"
                                        "氣慢慢交融，說不出的舒服受用。\n"
                                        "\n" NOR);
                } else
                {
                        set("skybook/item/xuanbingjiu", 1, me);
                        tell_object(me, HIW "\n你發覺體內陰陽兩種真氣慢慢"
                                        "交融，竟使得內功達到了一個前所未"
                                        "有的境界。\n\n" HIC "你對羅漢伏魔"
                                        "神功有了新的領悟。\n" NOR);
                        tell_object(me, HIC "你學會了「" HIW "冰" HIR "火"
                                        HIW "九重天" HIC "」。\n" NOR);
                        if (me->can_improve_skill("force"))
                                me->improve_skill("force", 1500000);
                        if (me->can_improve_skill("force"))
                                me->improve_skill("force", 1500000);
                        if (me->can_improve_skill("force"))
                                me->improve_skill("force", 1500000);
                        if (me->can_improve_skill("luohan-fumogong"))
                                me->improve_skill("luohan-fumogong", 1500000);
                        if (me->can_improve_skill("luohan-fumogong"))
                                me->improve_skill("luohan-fumogong", 1500000);
                        if (me->can_improve_skill("luohan-fumogong"))
                                me->improve_skill("luohan-fumogong", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        tell_object(me, "\n");
                }
        } else
                me->apply_condition("xuanbing-jiu", n);

        return 1;
}

int update_condition(object me, int duration)
{
        int limit;

        if( !living(me) && (query("eff_qi", me)<20
            || query("eff_jing", me)<10) )
        {
                set_temp("die_reason", "貪飲玄冰碧火酒，內息紊亂而亡", me);
                me->die();
                return 0;
        } else
        {
                me->receive_wound("qi", 20);
                me->receive_wound("jing", 10);

                if( query("max_neili", me) )
                        addn("max_neili", -1, me);

                switch (random(3))
                {
                case 0:
                        tell_object(me, HIR "突然間你只覺丹田處有如火燒，全身"
                                        "真氣鼓盪，便似要爆裂開一般。\n" NOR);
                        message("vision", HIR "忽見" + me->name() + HIR "須發"
                                "焦卷，全身散發著滾滾熱氣，嘶啞著嗓子亂嚎。\n"
                                NOR, environment(me), me);
                        break;

                case 1:
                        tell_object(me, HIW "霎時你只覺如同置身冰堅地獄，寒氣"
                                        "瞬間遊遍全身，說不出的難受。\n" NOR);
                        message("vision", HIW "忽見" + me->name() + HIW "散發"
                                "出絲絲寒氣，全身上下竟然被罩上了一層薄冰。\n"
                                NOR, environment(me), me);
                        break;

                default:
                        tell_object(me, HIB "你只覺丹田處兩種真氣相互抵觸，忽"
                                        "如" HIW "冰徹" NOR + HIB "，忽如" HIR
                                        "火炙" NOR + HIB "，苦不勘言。\n" NOR);
                        message("vision", HIB "突然" + me->name() + HIB "一聲"
                                "尖嘯，臉部扭曲得不成人樣，在地上不住顫抖。\n"
                                NOR, environment(me), me);
                        break;
                }
        }

        if( query("max_neili", me)<1 )
                set("max_neili", 0, me);

        me->apply_condition("xuanbing-jiu", duration - 1);

        if (! duration)
                return 0;

        return 1;
}
