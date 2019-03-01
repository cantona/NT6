#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        if (! target || ! me->is_fighting(target))
                return notify_fail("御劍飛升只能對戰鬥中的對手使用。\n");

        if( query_temp("jueji/sword/feisheng", me) )
                return notify_fail( WHT "你無法連續使用「御劍飛升」絕跡！\n" NOR );

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("sword", 1) < 400)
                return notify_fail("你的劍法尚達不到「御劍飛升」的境界。\n");

        if ((int)me->query_skill("force") < 400)
                return notify_fail("你的內功火候尚達不到「御劍飛升」的境界。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為太弱，無法靈活的御駕內力。\n");

        if( query("neili", me)<1500 )
                return notify_fail("你現在內力不夠。\n");

        msg = HIW "\n$N" HIW "一聲巨喝，聚氣入腕，只聽破空聲一響，手中"
             + weapon->name() + HIW "攜著隱隱風雷之勁向$n" HIW "澎湃貫"
              "\n出，疾若電閃，勢如雷霆。\n" NOR;

        damage = (int)me->query_skill("sword", 1) +
                 (int)me->query_skill("force", 1) +
                 (int)me->query_skill("parry", 1) +
                 (int)me->query_skill("martial-cognize", 1) / 2;

        damage = damage / 4 + random(damage / 4);

        me->start_busy(2 + random(4));
        set_temp("jueji/sword/feisheng", 1, me);
        call_out("end_perform2", 600, me, weapon, damage); 

        if (random(me->query_skill("force")) > target->query_skill("force") * 3 / 5)
        {
                addn("neili", -1000, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20,
                                           HIR "$n" HIR "看到$N" HIR "這氣拔千鈞的一擊，竟不"
                                           "知如何招架，登時受了重創！\n" NOR);
                message_vision(msg, me, target);
                remove_call_out("perform2");
                call_out("perform2", 2, me);
                return 1;
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，斜躍避開。\n" NOR;
                message_vision(msg, me, target);
                addn("neili", -100, me);
                remove_call_out("perform2");
                call_out("perform2", 2, me, target);
                return 1;
        }
        message_combatd(msg, me, target);

        return 1;
}

int perform2(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
        {
                write(HIW "你運轉內力，仰天一聲清嘯，劍在空中盤旋了一圈，又"
                      "飛回了你的手中。\n" NOR);
                call_out("end_perform2", 1, me, weapon, damage); 
                return 1;
        }

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
        {
                write(HIW "你停止使用「御劍飛升」絕技。\n" NOR);
                call_out("end_perform2", 30, me, weapon, damage); 
                return 1;
        }

        if( query("neili", me)<150 )
        {
                write(HIW "你劍至中途，可怎奈內息不足，只好停止御劍。\n" NOR);
                call_out("end_perform2", 30, me, weapon, damage); 
                return 1;
        }

        msg = HIW "\n$N" HIW "手中御劍凌駕如飛，宛若遊龍，靈轉千變，一道道"
                  "凌厲劍氣疾射而出。\n" NOR;

        if (random(me->query_skill("force")) > target->query_skill("force") / 2)
        {
                damage = (int)me->query_skill("sword", 1) +
                         (int)me->query_skill("force", 1) +
                         (int)me->query_skill("parry", 1) +
                         (int)me->query_skill("martial-cognize", 1) / 2;

                damage = damage / 5 + random(damage / 5);

                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20,
                                           HIR "只聽「嗤啦」一聲，" HIW "無形劍氣" NOR +
                                           HIR "竟在$n" HIR "上身刺出一個血洞，數股血柱"
                                           "疾射而出！\n" NOR);
                message_vision(msg, me, target);
                remove_call_out("perform2");
                call_out("perform2", 4, me);
                return 1;
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，斜躍避開。\n" NOR;
                message_vision(msg, me, target);
                addn("neili", -100, me);
                remove_call_out("perform2");
                call_out("perform2", 4, me);
                return 1;
        }
        message_combatd(msg, me, target);

        return 1;
}

void end_perform2(object me)
{
        if (! me) return;
        if( !query_temp("jueji/sword/feisheng", me))return ;
        delete_temp("jueji/sword/feisheng", me);
        tell_object(me, HIW "\n你經過調氣養息，又可以繼續使用「"
                        "御劍飛升」了。\n" NOR); 
}
