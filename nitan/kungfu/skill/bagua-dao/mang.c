#include <ansi.h>
#include <combat.h>


#define MANG "「" HIW "劈天神芒" NOR "」"

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/bagua-dao/mang", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(MANG "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" MANG "。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，難以施展" MANG "。\n");

        if (me->query_skill("wai-bagua", 1) < 140)
                return notify_fail("你的外八卦神功修為不夠，難以施展" MANG "。\n");

        if (me->query_skill("bagua-dao", 1) < 140)
                return notify_fail("你的八卦刀法修為不夠，難以施展" MANG "。\n");

        if (me->query_skill_mapped("blade") != "bagua-dao")
                return notify_fail("你沒有激發八卦刀法，難以施展" MANG "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" MANG "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "腳踏八卦四方之位，陡然一振手中" + weapon->name() +
              HIW "，刀身頓時捲起陣陣雪亮刀芒，將$n" + HIW "團團裹住！\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "只聽$n" HIR "一聲慘叫，一蓬血雨自" HIR
                                           "亮白的刀芒中飛濺而出！\n" NOR);
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "眼明手快，只聽叮叮噹噹響起了一串"
                       CYN "刀鳴，$p" CYN "將$P" CYN "的招式全部擋開！\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}