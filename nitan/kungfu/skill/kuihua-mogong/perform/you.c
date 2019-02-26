// you.c 幽冥一擊
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("幽冥一擊只能對戰鬥中的對手使用。\n");
 
        if (me->query_skill("kuihua-mogong", 1) < 120)
                return notify_fail("你的葵花魔功還不夠嫻熟，不能使用幽冥一擊！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠，不能使用幽冥一擊！\n");
                
        if (me->query_skill_mapped("force") != "kuihua-mogong")
                return notify_fail("你還沒有激發葵花魔功為內功，無法施展幽冥一擊。\n");  
                 
        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "忽的撲上前去，霎時便逼近$n" HIR
              "，忽的伸手猛然刺向$p的要害！\n" NOR;
 
        ap = attack_power(me, "force") + me->query_dex();
        dp = defense_power(target, "parry") + target->query_dex();

        me->start_busy(1);
        addn("neili", -40, me);

        if (ap * 2 / 3 + random(ap) < dp)
        {
                msg += HIG "然而$n" HIG "抵擋得法，將$N" HIG
                       "的攻勢一一化解。\n" NOR;
        } else
        {
                addn("neili", -60, me);
                damage = damage_power(me, "force") / 2 * 3;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                           HIR "$n" HIR "急忙後退，陣腳已亂，結果連中$N"
                                           HIR "數招，鮮血濺了一地！\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}