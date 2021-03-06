#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        object du;
        int an, dn, ap, dp;
        int f, i, skill;
        string msg;

        f = me->query_skill_mapped("force");
        skill = me->query_skill("force");

        if (me->query_skill_mapped("force") != "xiuluo-yinshagong"
           && me->query_skill_mapped("force") != "huagong-dafa"
           && me->query_skill_mapped("force") != "hama-gong"
           && me->query_skill_mapped("force") != "shennong-xinjing"
           && me->query_skill_mapped("force") != "huaxue-shengong")
                return notify_fail("你所學的內功中沒有這種功能。\n");

        if (skill < 150)
                return notify_fail("你的內功修為不夠。\n");

        if ((int)me->query_skill("poison", 1) < 100)
                return notify_fail("你的基本毒技火候不夠。\n");

        if ((int)me->query_skill("throwing", 1) < 100)
                return notify_fail("你的基本暗器火候不夠。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("在這裏不能攻擊他人。\n");

        // 執行天書任務的特殊房間防止彈毒中斷劇情。
        if( query("skybook", environment(me)) )
                return notify_fail("在這裏不能攻擊他人。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠。\n");

        if( !objectp(du=query_temp("handing", me)) )
                return notify_fail("你得先準備(hand)好毒藥再説。\n");

        if( !mapp(query("poison", du)) )
                return notify_fail("你手中所拿的" + du->name() + NOR
                                   "不是毒藥，無法彈射。\n");

        if( query("no_shot", du) )
                return notify_fail("將" + du->name() + NOR "彈射出去"
                                   "？似乎不太好吧。\n");

        if (! target || me == target
           || ! target->is_character()
            || query("not_living", target) )
                return notify_fail("你想攻擊誰？\n");

        if (target->query_condition("die_guard"))
                return notify_fail("這個人正被官府保護着，還是別去招惹。\n");

        if (target->query_competitor())
                return notify_fail("比武的時候最好是正大光明的較量。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIM "$N" HIM "一聲冷笑，默運" + to_chinese(f) +
              HIM "內勁，手指粘住" + du->name() +
              HIM "對準$n" HIM "「嗖」的彈射了出去。\n" NOR;

        me->start_busy(1 + random(3));
        addn("neili", -100, me);

        an=query("max_neili", me)+query("neili", me)/2;
        dn=query("max_neili", target)+query("neili", target)/2;

        if (an / 2 + random(an) < dn * 2 / 3)
        {
                msg += WHT "然而$n" WHT "全然不放在心上，輕輕一抖，已將$N"
                       WHT "射來的毒素盡數震落。\n" NOR;
        } else
        {
                ap = me->query_skill("force") +
                     me->query_skill("poison") +
                     me->query_skill("throwing");

                dp = target->query_skill("dodge") +
                     target->query_skill("parry") +
                     target->query_skill("martial-cognize");

                if (ap / 2 + random(ap) > dp)
                {
                        msg += HIG "$n" HIG "急忙飛身躲避，可已然不及，霎時"
                               "綠光閃過，$p" HIG "頓感一陣麻痺。\n" NOR;
                        target->affect_by(query("poison_type", du),
                                          query("poison", du));

                        if (! target->is_busy())
                                target->start_busy(2);
                } else
                {
                        msg += CYN "可是$n" CYN "見勢不妙，急忙騰挪身形，終"
                               "於避開了$N" CYN "的彈毒攻擊。\n" NOR;
                }
        }
        message_combatd(msg, me, target);

        if (du->query_amount())
        {
                du->add_amount(-1);

                if (du->query_amount() < 1)
                        destruct(du);
        } else
                destruct(du);

        me->want_kill(target);

        if (! target->is_killing(me))
                target->kill_ob(me);

        return 1;
}
