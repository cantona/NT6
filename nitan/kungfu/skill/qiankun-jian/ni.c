#include <ansi.h>
#include <combat.h>

#define NI "「" HIW "逆轉乾坤" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/qiankun-jian/ni", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(NI "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" NI "。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的內功的修為不夠，難以施展" NI "。\n");

        if (me->query_skill("qiankun-jian", 1) < 180)
                return notify_fail("你的乾坤神劍修為不夠，難以施展" NI "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，難以施展" NI "。\n");

        if (me->query_skill_mapped("sword") != "qiankun-jian")
                return notify_fail("你沒有激發乾坤神劍，難以施展" NI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "一聲清嘯，手中" + weapon->name() +
              HIW "一振，將乾坤劍法逆行施展，頓時劍影重重，萬"
              "道光華直追$n" + HIW "而去！\n" NOR;

        ap = me->query_skill("sword") + me->query_skill("force");
        dp = target->query_skill("dodge") + target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 3 + random(ap / 3);
                addn("neili", -200, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "完全無法看清招中虛實，微"
                                           "微一楞間，發現" + weapon->name() + HIR
                                           "竟已沒入自己胸口數寸。\n" NOR);
        } else
        {
                addn("neili", -80, me);
                me->start_busy(4);
                msg += CYN "可是$n" CYN "看破" CYN "$N" CYN
                       "的招數，飛身一躍，閃開了這神鬼莫測"
                       "的一擊。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
