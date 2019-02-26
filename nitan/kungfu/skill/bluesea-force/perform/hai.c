#include <ansi.h>
#include <combat.h>

#define HAI "「" HIG "苦海無邊" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

string *finger_name = ({ "左手中指", "左手無名指", "左手食指",
                         "右手中指", "右手無名指", "右手食指", }); 

int perform(object me, object target)
{
        int damage;
        string msg, name;
        object weapon;
        int lvl, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HAI "只能對戰鬥中的對手使用。\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "staff" )
                        return notify_fail("你手裏拿的不是杖，怎麼施展" HAI "？\n");
        } else
        {
                if (me->query_skill_prepared("finger") != "bluesea-force")
                        return notify_fail("你並沒有準備使用南"
                                           "海玄功，如何施展" HAI "？\n");
        }

        if ((int)me->query_skill("bluesea-force", 1) < 260)
                return notify_fail("你的南海玄功不夠嫻熟，難以施展" HAI "。\n");

        if( query("max_neili", me)<3700 )
                return notify_fail("你的內力修為不足，難以施展" HAI "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不足，難以施展" HAI "。\n");
                
        if (weapon && me->query_skill_mapped("staff") != "bluesea-force")
                return notify_fail("你沒有準備使用南海玄功，難以施展" HAI "。\n");

        if (! weapon && me->query_skill_prepared("finger") != "bluesea-force")
                return notify_fail("你沒有準備使用南海玄功，難以施展" HAI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        /*
        if (target->query_condition("no_exert"))
                return notify_fail("對方現在已經無法控制真氣，放膽攻擊吧。\n");
        */

        if( query_temp("weapon", me) )
                name = "手中" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        msg = HIB "$N" HIB "氣貫雙臂，向地一擊，一股氣浪卷着飛石如狂濤般襲向$n" HIB "，對方驚魂未定之際，忽聞三聲輕響。\n"
              HIB "自$N" HIB "的" + name + HIB "中射出三道玄勁，分襲$n" HIB "三處死穴“雲門穴、章門穴、啞門穴”。\n\n" NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "force");

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                          (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -500, me);
        } else
        {
                msg += CYN "$n" CYN "慌亂中一個鴿子翻身，躍出數丈，"
                       "僥倖躲開了這一招。\n" NOR;
                me->start_busy(3);
                addn("neili", -350, me);
        }
        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int ap)
{
        if (target->query_condition("no_exert")) return "";
        target->apply_condition("no_exert", 30);
        call_out("hai_end", 15 + random(ap / 20), me, target);
        return HIY "$n" HIY "只覺眼前飛沙走石，目不能視，忽覺身上要穴"
               "刺痛，三道血柱自身上射出。\n$p陡然間一提真氣，"
               "竟覺得丹田之內空虛若谷，全然無法運氣。\n" NOR;
}

void bian_end(object me, object target)
{
        if (target && target->query_condition("no_exert"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "氣，臉色由白轉紅，看起來好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被擾亂的真氣"
                                            "慢慢平靜了下來。\n" NOR);
                }
                target->clear_condition("no_exert");
        }
        return;
}