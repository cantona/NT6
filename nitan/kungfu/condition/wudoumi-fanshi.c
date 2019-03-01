// wudoumi-fanshi.c
// 五鬥米神功反噬

#include <ansi.h>
inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
        int f, n, lvl;
        f = me->query_skill_mapped("force");
        lvl = me->query_skill("force");

        if (me != ob)
        {
                tell_object(ob, "你發覺" + me->name() + "的內力源源湧進，使丹"
                            "田處燃燒得更為厲害，便如身陷洪爐，眼前登時一黑。\n");
                tell_object(me, "你試圖幫助" + ob->name() + "化解異種真氣，卻"
                            "發現對方真氣便似洪爐爆裂，不由大驚，連忙住手。\n");

                if (living(ob))
                        ob->unconcious();

                return -1;
        }

        if (me->query_skill_mapped("force") != "yijin-duangu"
           && me->query_skill_mapped("force") != "jiuyin-shengong"
           && me->query_skill_mapped("force") != "shaolin-jiuyang"
           && me->query_skill_mapped("force") != "wudang-jiuyang"
           && me->query_skill_mapped("force") != "emei-jiuyang"
           && me->query_skill_mapped("force") != "jiuyang-shengong"
           && me->query_skill_mapped("force") != "taiji-shengong"
           && me->query_skill_mapped("force") != "xuanmen-neigong"
           && me->query_skill_mapped("force") != "xiantian-gong")
        {
                tell_object(me, "你覺得全身真氣猶如洪爐爆裂，內息"
                                "根本無法凝聚。\n");
                return -1;
        }

        n = me->query_condition("wudoumi-fanshi") - lvl / 15;
        if (n < 1)
                me->clear_condition("wudoumi-fanshi");
        else
                me->apply_condition("wudoumi-fanshi", n);

        tell_object(me, "你默默的運用" + to_chinese(f) + "化解體內"
                        "的異種真氣。\n");

        return 1;
}

int update_condition(object me, int duration)
{
        int limit;

        if (! living(me) && (me->query("eff_qi") < 20 || me->query("eff_jing") < 10))
        {
                me->set_temp("修習五鬥米神功不慎，被內力反噬吐血而亡");
                me->die();
                return 0;
        } else
        {
                me->receive_wound("qi", 20);
                me->receive_wound("jing", 10);

                if (me->query("max_neili"))
                        me->add("max_neili", -1);

                tell_object(me, HIR "你覺得丹田處如同火燒，全身真氣鼓盪"
                                "不止，便似要破體而出一般。\n" NOR);
                message("vision", HIR + me->name() + HIR "臉色赤紅，須發"
                                  "焦卷，全身散發著滾滾熱氣，不住的顫抖。\n",
                                  environment(me), me);
        }

        if (me->query("max_neili") < 1)
                me->set("max_neili", 0);

        me->apply_condition("wudoumi-fanshi", duration - 1);

        if (! duration)
                return 0;

        return 1;
}
