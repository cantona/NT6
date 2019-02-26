#include <ansi.h>
#include <combat.h>

#define BIAN "「" HIG "無邊無際" NOR "」"

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
                return notify_fail(BIAN "只能對戰鬥中的對手使用。\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "sword" && 
                    query("skill_type", weapon) != "pin" )
                        return notify_fail("你手裏拿的不是劍，怎麼施"
                                           "展" BIAN "？\n");
        } else
        {
                if (me->query_skill_prepared("finger") != "kuihua-mogong")
                        return notify_fail("你並沒有準備使用葵"
                                           "花魔功，如何施展" BIAN "？\n");
        }

        if ((int)me->query_skill("kuihua-mogong", 1) < 260)
                return notify_fail("你的葵花魔功不夠嫻熟，難以施展" BIAN "。\n");

        if( query("max_neili", me)<3700 )
                return notify_fail("你的內力修為不足，難以施展" BIAN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不足，難以施展" BIAN "。\n");

        if (me->query_skill_mapped("force") != "kuihua-mogong")
                return notify_fail("你沒有激發葵花魔功為特殊內功，難以施展" BIAN "。\n");
                
        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("你沒有準備使用葵花魔功，難以施展" BIAN "。\n");

        if (! weapon && me->query_skill_prepared("finger") != "kuihua-mogong")
                return notify_fail("你沒有準備使用葵花魔功，難以施展" BIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        if( query_temp("no_perform", target) )
                return notify_fail("對方現在已經無法控制真氣，放膽攻擊吧。\n");

        if( query_temp("weapon", me) )
                name = "手中" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        msg = HIR "$N" HIR "一聲尖嘯，身體猛然旋轉不定，" + name +
              HIR "頓時化成無數氣流，猶如千萬根銀針，齊齊卷向$n" HIR "！\n" NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "force");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                          (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -200, me);
        } else
        {
                msg += CYN "$n" CYN "大驚之下全然無法招架，急忙"
                       "抽身急退數尺，躲開了這一招。\n" NOR;
                me->start_busy(3);
                addn("neili", -150, me);
        }
        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int ap)
{
        int t = 3 + random(4);
        target->apply_condition("no_perform", t);
        call_out("bian_end", t, me, target);
        return HIR "$n" HIR "只覺眼前無數寒光閃過，隨即全身一陣"
               "刺痛，幾股血柱自身上射出。\n$p陡然間一提真氣，"
               "竟發現周身力道竟似渙散一般，全然無法控制。\n" NOR;
}

void bian_end(object me, object target)
{
        if (target && target->query_condition("no_perform"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "氣，臉色由白轉紅，看起來好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被擾亂的真氣"
                                            "慢慢平靜了下來。\n" NOR);
                }
                target->clear_condition("no_perform");
        }
        return;
}