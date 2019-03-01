#include <ansi.h>
#include <combat.h>

string name() { return HIM "小樓一夜聽春雨" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp, md, ly;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("moon-blade", 1) < 200)
                return notify_fail("你的圓月彎刀還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "moon-blade")
                return notify_fail("你沒有激發圓月彎刀，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HBRED "小樓一夜聽春雨：圓月落，刀光起。縱橫大地十萬裡。刀光寒如雪，何處聽春雨？\n" NOR
              HIY "只聽唰的一聲，" + weapon->name() + HIY "出手了！一切只能以一個快字去形容，發生在肉眼難看清楚的高速下，\n"
              "$N" HIY "這一刀劈出時，好像也是直直的，但是這筆直劈出來的一刀，竟忽然閃起了一道彎彎的刀光。\n"
              "彎彎的刀，彎彎的刀光，開始時宛如一彎新月，忽然間就變成了一道飛虹。這一道彎彎的刀光閃起時，\n"
              + weapon->name() + HIY "上的妖異之氣，使人為之震眩迷惑。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        md = me->query_skill("moon-blade", 1);
        ly = target->query_skill("lonely-sword", 1);

        if (ap * 2 / 3 + random(ap) > dp )
        {
                damage = 0;
                if (me->query_skill("blade") > target->query_skill("force") &&
                    query("reborn/times", me) >= query("reborn/times", target) && random(md)>ly )
                {
                        me->start_busy(2);
                        addn("neili", -100, me);
                        msg += HIR "當$n" HIR "感到$N" HIR "出手時，" + weapon->name() + HIR "早已揮出，化作滿月時的月光，劃過兩丈的虛空劈向$n。\n"
                               "$n" HIR "只感到周遭所有的氣流和生氣都似被$N" HIR "這驚天動地的一招吸個一絲不剩，一派生機盡絕，\n"
                               "死亡和肅殺的駭人味兒。只聽得輕輕的一聲響，那道彎彎的刀光卻還在，又彎彎地一轉。然後美如月光的刀氣消失了，\n"
                               "所有的聲音都沉寂，所有的動作都停頓。$N" HIR "還是像一瞬前那麼樣靜靜地站在那裡，好像根本沒有動過。可是$N"
                               HIR "手裡的" + weapon->name() + HIR "已經在滴著血。\n" NOR;
                        damage = -1;
                } else
                {
                        me->start_busy(2);
                        addn("neili", -600, me);
                        damage = damage_power(me, "blade");
                        damage+= query("jiali", me);
                        damage*= 3;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                                   HIR "結果$p" HIR "閃避不及，只覺得"
                                                   "一股冰寒的刀氣掠過全身，$n全身頓時鮮血淋漓！\n" NOR);
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -300, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}

