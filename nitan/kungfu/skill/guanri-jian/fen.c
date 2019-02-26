#include <ansi.h>
#include <combat.h>

string name() { return HIR "焚陽劍" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" +name()+ "。\n");

        if ((int)me->query_skill("guanri-jian", 1) < 150)
                return notify_fail("你觀日劍法不夠嫻熟，難以施展" +name()+ "。\n");

        if (me->query_skill_mapped("sword") != "guanri-jian")
                return notify_fail("你沒有激發觀日劍法，難以施展" +name()+ "。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不夠，難以施展" +name()+ "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" +name()+ "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = WHT "$N" WHT "運轉內力，陡然一勢「" HIR "焚陽劍" NOR +
              WHT "」劃出，手中" + weapon->name() + WHT "攜着一股熱"
              "流卷向$n" WHT "全身。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           (: final, me, target, damage :));

                me->start_busy(3);
                addn("neili", -300, me);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$N"
                       CYN "的企圖，斜躍避開。\n" NOR;
                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("guanri-jian", 1);

        target->affect_by("zhurong_jian",
                ([ "level"    : lvl + random(lvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ]));

        return  HIR "只聽$n" HIR "一聲慘嚎，幾柱鮮血射出，劍傷"
                "處騰起一道烈火，燒得嗤嗤作響。\n" NOR;
}
