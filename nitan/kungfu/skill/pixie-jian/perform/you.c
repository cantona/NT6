// you.c 幽冥一擊

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "幽冥一擊"; }

int perform(object me, object target)
{
        string msg;
        int ap, dp, bs;
        int damage;
        object weapon;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( query("gender", me) != "無性" && !query("reborn/times", me) )
                return notify_fail("你的性別與日月內功相斥，無法使用此絕招！\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("幽冥一擊只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你沒有裝備劍，不能用這一招。\n");

        if( me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("你並沒有使用辟邪劍法，無法使用此絕招！\n");

        if (me->query_skill("pixie-jian", 1) < 400)
                return notify_fail("你的辟邪劍法還不夠嫻熟，不能使用幽冥一擊！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠，不能使用幽冥一擊！\n");

        msg = HIR "$N" HIR "忽的撲上前去，霎時便逼近$n" HIR
              "，手中" + weapon->name() + HIR "猛然刺向$p的要害！\n" NOR;

        ap=attack_power(me,"sword")+me->query_dex()*20;
        dp=defense_power(target,"parry")+target->query_dex()*20;

        me->start_busy(2);
        addn("neili", -40, me);

        if (ap / 2 + random(ap*2) < dp || !living(target))
        {
                msg += HIG "然而$n" HIG "抵擋得法，將$N" HIG
                       "的攻勢一一化解。\n" NOR;
        } else
        {
                if (! target->is_busy())
                        target->start_busy(1);
                addn("neili", -60, me);
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 65,
                                           HIR "$n" HIR "急忙後退，陣腳已亂，結果連中$N"
                                           HIR "數招，鮮血濺了一地！\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}
