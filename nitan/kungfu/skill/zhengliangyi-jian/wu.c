#include <ansi.h>
#include <combat.h>

#define WU "「" HIW "無聲無色" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/zhengliangyi-jian/wu", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( query("no_fight", environment(me)) )
                return notify_fail("在這裏不能攻擊他人。\n");

        // 執行天書任務的特殊房間防止龍吟中斷劇情。
        if( query("skybook", environment(me)) )
                return notify_fail("在這裏不能攻擊他人。\n");

        if (! target || ! target->is_character()
            || query("not_living", target) )
                return notify_fail(WU "只能對對手使用。\n");

        if (target == me)
                return notify_fail("你打算攻擊自己？\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，無法施展" WU "。\n");

        if ((int)me->query_skill("zhengliangyi-jian", 1) < 160)
                return notify_fail("你的正兩儀劍法不夠嫻熟，難以施展" WU "。\n");

        if ((int)me->query_skill("dodge") < 220)
                return notify_fail("你的輕功火候不足，難以施展" WU "。\n");

        if (me->query_dex() < 45)
                return notify_fail("你現在身法太差，難以施展" WU "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，難以施展" WU "。\n");

        if (me->query_skill_mapped("sword") != "zhengliangyi-jian") 
                return notify_fail("你沒有激發正兩儀劍法，難以施展" WU "。\n");

        if ((int)target->query_condition("die_guard"))
                return notify_fail("對方正被官府保護着呢，還是別去招惹。\n");

        if (target->query_competitor())
                return notify_fail("比武的時候最好是正大光明的較量。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "一聲陰笑，突然使出一招「無聲無色」，疾向$n"
              HIW "背後刺去。\n" NOR;

        addn("neili", -200, me);
        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        me->start_busy(2);
        if (ap / 2 + random(ap) > dp)
        {
                damage = ap * 2 / 3 + random(ap / 3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIC "可是$p" HIC "看破了$P" HIC "的企圖，飛身"
                       "一躍而起，將$P" HIC "這招化解於無形。\n" NOR;
        }
        message_combatd(msg, me, target);
        me->want_kill(target);

        if (! target->is_killing(me))
                target->kill_ob(me);
        return 1;
}

string final(object me, object target, int damage)
{
        object weapon;
        weapon=query_temp("weapon", me);

        return  HIW "結果$n" HIW "並沒有察覺$N" HIW "的殺意，絲毫沒把"
                "這一招放在心上，只\n是身子略微的向前一傾。\n" NOR +
                HIR "霎時只見$N" HIR "招數一緊，頓時只聽“嗤啦”一聲"
                "破空之響，$n" HIR "\n一聲慘嚎，" + weapon->name() +
                HIR "劍身已透背而入。\n" NOR;
}