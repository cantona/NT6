#include <ansi.h>
#include <combat.h>

#define PAN "「" HIR "蝰蟒盤身" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/kuimang-dao/pan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(PAN "只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" PAN "。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功火候不夠，難以施展" PAN "。\n");

        if ((int)me->query_skill("kuimang-dao", 1) < 40)
                return notify_fail("你的蝰蟒刀法還不到家，難以施展" PAN "。\n");

        if (me->query_skill_mapped("blade") != "kuimang-dao")
                return notify_fail("你沒有激發蝰蟒刀法，難以施展" PAN "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的真氣不夠，難以施展" PAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "手中" + weapon->name() +  HIR "翻轉不定，忽然只見刀"
              "光一閃，刀鋒已向$n" HIR "斜斜撩去。\n" NOR;

        ap = me->query_skill("blade");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 3 + random(ap / 3);
                addn("neili", -30, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20,
                                           HIR "$n" HIR "微微一愣間，已被$N" HIR
                                           "刀鋒帶中，劃出一道鮮血淋漓的傷口！\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "可是$p" CYN "微微一笑，身子朝一旁偏過尺許，躲開$P"
                       CYN "這一刀。\n" NOR;
                addn("neili", -10, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}