#include <ansi.h>
#include <combat.h>

#define ZHUI "「" HIR "追魂奪命" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/zhuihun-jian/zhui", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUI "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" ZHUI "。\n");

        if (me->query_skill_mapped("sword") != "zhuihun-jian") 
                return notify_fail("你沒有激發追魂奪命劍，難以施展" ZHUI "。\n");

        if ((int)me->query_skill("zhuihun-jian", 1) < 100)
                return notify_fail("你的追魂奪命劍還不夠嫻熟，難以施展" ZHUI "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，難以施展" ZHUI "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "一聲冷哼，手中" + weapon->name() +
              HIR "一式「追魂奪命」，劍身頓時漾起一道血光，直射$n"
              HIR "！\n" NOR;

        addn("neili", -150, me);
        ap = me->query_skill("sword");
        dp = target->query_skill("dodge");
        if (target->is_bad()) ap += ap / 5;

        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           (: final, me, target, damage :));
        } else
        {
                msg += CYN "可$n" CYN "卻是鎮定逾恆，一絲不亂，"
                       "全神將此招化解開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        return  HIR "只聽$n" HIR "一聲慘叫，被這一劍穿胸而入，頓"
                "時鮮血四處飛濺。\n" NOR;
}