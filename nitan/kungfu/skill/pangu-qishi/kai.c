#include <ansi.h>
#include <combat.h>

#define KAI "「" HIY "開天辟地" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/pangu-qishi/kai", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KAI "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "hammer" )
                return notify_fail("你使用的武器不對，難以施展" KAI "。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的內功的修為不夠，難以施展" KAI "。\n");

        if (me->query_skill("pangu-qishi", 1) < 180)
                return notify_fail("你的盤古七勢修為不夠，難以施展" KAI "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，難以施展" KAI "。\n");

        if (me->query_skill_mapped("hammer") != "pangu-qishi")
                return notify_fail("你沒有激發盤古七勢，難以施展" KAI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "一聲斷喝，手中" + weapon->name() +
              WHT "如山岳巍峙，攜著開天辟地之勢向$n" WHT "猛劈而下！\n" NOR;

        ap=me->query_skill("hammer")+query("str", me)*10;
        dp=target->query_skill("force")+query("con", target)*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap);
                addn("neili", -500, me);
                me->start_busy(5);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "躲避不及，被$N" HIR "這"
                                           "錘正中胸口，頓時一聲悶響，稻草般向後"
                                           "橫飛出去。\n" NOR);
        } else
        {
                addn("neili", -300, me);
                me->start_busy(6);
                msg += HIC "可是$n" HIC "真氣鼓盪，$N" HIC "雷霆般"
                       "的勁力竟如中敗絮，登時被解于無形。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}