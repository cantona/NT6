#include <ansi.h>
#include <combat.h>

#define SHA "「" HIR "無痕殺" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/shiying-lianhuan/sha", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHA "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" SHA "。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功修為不夠，難以施展" SHA "。\n");

        if (me->query_skill("shiying-lianhuan", 1) < 150)
                return notify_fail("你弒鷹九連環修為不夠，難以施展" SHA "。\n");

        if (me->query_skill_mapped("blade") != "shiying-lianhuan")
                return notify_fail("你沒有激發弒鷹九連環，難以施展" SHA "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不足，難以施展" SHA "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "迴轉手中" + weapon->name() + HIR "施出「" NOR +
              RED "無痕殺" HIR "」絕技，刀身頓時漾起一道血色刀芒，直斬$n"
              HIR "而去！\n" NOR;

        ap = me->query_skill("blade");
        dp = target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap);
                addn("neili", -250, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "只聽“嗤啦”一聲，$n" HIR "被$N"
                                           HIR "的刀芒劃中氣門，登時痛聲長呼，幾"
                                           "欲暈倒。\n" NOR);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(4);
                msg += CYN "$n" CYN "見$P" CYN "來勢洶湧，連忙飛"
                       "身向後挪移數尺，躲閃開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}