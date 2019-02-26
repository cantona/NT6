#include <ansi.h>
#include <combat.h>

#define PO "「" HIW "破元劍閃" NOR "」"

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

        if( userp(me) && !query("can_perform/pixie-jian/po", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(PO "只能對戰鬥中的對手使用。\n");

        weapon=query_temp("weapon", me);

        if( weapon && query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "pin" )
                return notify_fail("你使用的武器不對，難以施展" PO "。\n");

        if ((int)me->query_skill("pixie-jian", 1) < 180)
                return notify_fail("你的辟邪劍法不夠嫻熟，難以施展" PO "。\n");

        if( query("max_neili", me)<2600 )
                return notify_fail("你的內力修為不足，難以施展" PO "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不足，難以施展" PO "。\n");

        if (weapon && me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("你沒有準備使用辟邪劍法，難以施展" PO "。\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "pixie-jian")
                return notify_fail("你沒有準備使用辟邪劍法，難以施展" PO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        if( query_temp("no_perform", target) )
                return notify_fail("對方現在已經無法控制真氣，放膽攻擊吧。\n");

        if( query_temp("weapon", me) )
                name = "手中" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        msg = HIW "$N" HIW "一聲冷哼，雙眸間透出一絲寒氣，" + name +
              HIW "化作千百根相似，幻出死亡的色彩！\n" NOR;

        ap = me->query_skill("sword") +
             me->query_skill("dodge");

        dp = target->query_skill("parry") +
             target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, random(15) + 80,
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
        set_temp("no_perform", 1, target);
        call_out("poyuan_end", 10 + random(ap / 30), me, target);
        return HIR "$n" HIR "只覺眼前寒芒一閃而過，隨即全身一陣"
               "刺痛，幾股血柱自身上射出。\n$p陡然間一提真氣，"
               "竟發現周身力道竟似渙散一般，全然無法控制。\n" NOR;
}

void poyuan_end(object me, object target)
{
        if( target && query_temp("no_perform", target) )
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "氣，臉色由白轉紅，看起來好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被擾亂的真氣"
                                            "慢慢平靜了下來。\n" NOR);
                }
                delete_temp("no_perform", target);
        }
        return;
}
