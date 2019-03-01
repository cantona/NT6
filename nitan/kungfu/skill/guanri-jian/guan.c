#include <ansi.h>
#include <combat.h>

string name() { return HIW "天洪地爐觀" HIR "日" HIW "神訣" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int i, count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" +name()+ "。\n");

        if ((int)me->query_skill("guanri-jian", 1) < 280)
                return notify_fail("你觀日劍法不夠嫻熟，難以施展" +name()+ "。\n");

        if (me->query_skill_mapped("sword") != "guanri-jian")
                return notify_fail("你沒有激發觀日劍法，難以施展" +name()+ "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不夠，難以施展" +name()+ "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在的真氣不足，難以施展" +name()+ "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "施出觀日劍法之「" HIW "天洪地爐觀"
              HIR "日" HIW "神訣" NOR + WHT "」，將內力盡數注"
              "入" + weapon->name() + WHT "劍身直奔\n$n" WHT
              "而去。霎時間熾炎暴漲，熱浪撲面卷來，四周空氣便"
              "似沸騰一般。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        me->start_busy(3);
        addn("neili", -600, me);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           (: final, me, target, damage :));
        } else
        {
                me->start_busy(2);
                msg += CYN "可是$n" CYN "看破了$N" CYN "的企圖，斜躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        count = me->query_skill("sword");
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);

        message_combatd(WHT "緊跟著$N" WHT "一聲冷笑，身形驀地前躍丈"
                        "許，手中" + weapon->name() + WHT "「唰唰唰」"
                        "連出九劍。\n" NOR, me, target);

        for (i = 0; i < 9; i++)
              {
                       if (! me->is_fighting(target))
                               break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);

        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("guanri-jian", 1);

        target->affect_by("zhurong_jian",
                ([ "level"    : lvl + random(lvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ]));

        return  HIR "只聽$p" HIR "一聲慘嚎，幾柱鮮血射出，劍傷"
                "處竟騰起一道烈火，燒得嗤嗤作響。\n" NOR;
}
