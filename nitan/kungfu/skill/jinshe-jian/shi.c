#include <ansi.h>
#include <combat.h>

#define SHEN "「" HIY "金蛇噬天" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
        me = this_player();
        /*
        if( userp(me) && !query("can_perform/jinshe-jian/shi", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");
        */
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHEN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" SHEN "。\n");

        if ((int)me->query_skill("jinshe-jian", 1) < 200)
                return notify_fail("你金蛇劍法不夠嫻熟，難以施展" SHEN "。\n");

        if (me->query_skill_mapped("sword") != "jinshe-jian")
                return notify_fail("你沒有激發衡山五神劍，難以施展" SHEN "。\n");

        if ((int)me->query_skill("force", 1) < 240)
                return notify_fail("你的內功火候不夠，難以施展" SHEN "。\n");

        if ((int)me->query_skill("dodge", 1) < 240)
                return notify_fail("你的輕功火候不夠，難以施展" SHEN "。\n");  

        if( query("max_neili", me)<4500 )
                return notify_fail("你的內力修為不足，難以施展" SHEN "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在的真氣不夠，難以施展" SHEN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();

        msg = HIY "一道金光劃過，$N" HIY "消失得無影無蹤，猛然間只見一條"
              "金蛇從天而下，" + weapon->name() + HIY "已將$n" HIY "籠罩。\n" NOR;

        message_sort(msg, me, target);
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                // 十分之一的機率可被招架
                if (random(10) <= 1 && ap / 2 < dp)
                {
                        damage = damage / 3;

                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                                  HIG "$n" HIG "見$N" HIG "一道金光閃過"
                                                  "，急忙收斂心神奮力招架。哪知$P這"
                                                  "招力道非凡，$p一聲悶哼，連退幾步，噴"
                                                  "出一口鮮血。\n" NOR);
                        addn("neili", -200, me);
                        me->start_busy(3 + random(2));
                } else 
                {
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                                  HIR "$n" HIR "見$N" HIR "金光劃過，心"
                                                  "底不由大驚，登時聽得“噗嗤”一聲，劍"
                                                  "氣透體而過。\n" NOR);
                        addn("neili", -300, me);
                        me->start_busy(2 + random(3));
                }
        } else
        {
                msg = CYN "\n然而$n" CYN "以快對快，飛身一跳"
                      "已然躲過$N" CYN "這一招。\n" NOR;
                addn("neili", -150, me);
                me->start_busy(2);
        }
        message_sort(msg, me, target);
        return 1;
}