#include <ansi.h>
#include <combat.h>

#define LUAN "「" HIW "百花錯亂" NOR "」"

inherit F_SSERVER;


int perform(object me, object target)
{
        int skill, ap, dp, damage;
        string msg;

        if( userp(me) && !query("can_perform/baihua-cuoquan/luan", me) )
                return notify_fail("你還沒有受到高手指點，還不會運用" LUAN "。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(LUAN "只能對戰鬥中的對手使用。\n");

        skill = me->query_skill("baihua-cuoquan", 1);

        if (skill < 120)
                return notify_fail("你的百花錯拳等級不夠，難以施展" LUAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" LUAN "。\n");
 
        if (me->query_skill_mapped("unarmed") != "baihua-cuoquan")
                return notify_fail("你沒有激發百花錯拳，難以施展" LUAN "。\n");

        if (me->query_skill_prepared("unarmed") != "baihua-cuoquan")
                return notify_fail("你現在沒有準備使用百花錯拳，無法使用" LUAN "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "頓步沉身，雙掌朝$n" HIW "交錯打出，掌鋒拳影重"
              "重疊疊，正是一招「百花錯亂」。\n" NOR;
        addn("neili", -50, me);

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -150, me);
                damage = damage_power(me, "unarmed");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIW "$n只感到頭暈目眩，只見$N或掌、或爪、"
                                           "或拳、或指鋪天蓋地的向自己各個部位襲來！\n"
                                           "只一瞬間，全身竟已多了數十出傷痕，" 
                                           HIR "鮮血" HIW "狂瀉不止！\n" NOR);
                me->start_busy(1);
                if (! target->is_busy())
                        target->start_busy(ap / 500 + 2);
        } else
        {
                msg += CYN "$n" CYN "只見$N" CYN "拳勢洶湧，不敢輕視，急忙凝神聚"
                       "氣，奮力化解開來。\n" NOR;
                addn("neili", -80, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}