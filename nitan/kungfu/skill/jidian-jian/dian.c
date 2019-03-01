#include <ansi.h>
#include <combat.h>

#define DIAN "「" HIY "電光四射" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/jidian-jian/dian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(DIAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器無法施展" DIAN "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功的修為不夠，無法施展" DIAN "。\n");

        if (me->query_skill("jidian-jian", 1) < 100)
                return notify_fail("你的疾電劍法修為不夠，無法施展" DIAN "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，無法施展" DIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "冷哼一聲，手中" + weapon->name() + NOR + HIY
              "一抖，運劍如飛，霎時之間，四處都是電光，耀人眼目。\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                addn("neili", -180, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "只聽“唰唰唰”幾聲，$n" HIR "無法"
                                           "看透招中虛實，連續被削中數劍，一聲慘"
                                           "叫，血如泉湧！\n" NOR );
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "奮力格擋，$P" CYN "只"
                       "覺得對手防守嚴密，手中劍光漸緩。 \n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}