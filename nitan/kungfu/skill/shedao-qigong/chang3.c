// 唱仙法吼字決

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "吼字決"; }
int perform(object me, object target)
{
        string msg;
        int neili, damage;
        int i;
        int ap, dp;

        if (! target ) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("唱仙法吼字決只能在戰鬥中對對手使用。\n");

        if ((int)me->query_skill("shedao-qigong", 1) < 100)
                return notify_fail("你的蛇島奇功不夠嫻熟，不會使用唱仙法吼字決。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("在這裡不能攻擊他人。\n");

        if( query("neili", me)<500 )
                return notify_fail("你已經精疲力竭，真氣不夠了。\n");

        if (me->query_skill_mapped("unarmed") != "shedao-qigong")
                return notify_fail("你沒有將基本拳腳"
                                   "激發為蛇島奇功, 不能使用「吼字決」！\n");

        //neili=query("max_neili", me);
        neili=query("neili", me);
        if( neili > query("max_neili", me)*2 )
                neili = query("max_neili", me) * 2;

        addn("neili", -(300+random(200)), me);
        //me->receive_damage("qi", 10);

        // me->start_busy(1 + random(5));

        message_combatd(HIY "$N" HIY "深深地吸一囗氣，忽然仰天長嘯，高"
                        "聲狂叫：不死神龍，唯我不敗！\n" NOR, me);

        if( neili/2+random(neili/2)<query("max_neili", target) )
                return notify_fail("敵人的內力不遜于你，傷不了！\n");

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "force");

        msg = "";
        if (ap / 2 + random(ap) > dp)
        {
                damage=(neili-query("max_neili", target))/2;
                if (damage > 0)
                {
                        damage+= query("jiali", me);
                        target->receive_damage("jing", damage, me);
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("jing", damage / 4, me);
                        target->receive_wound("qi", damage / 4, me);
                        message_combatd(HIR "$N" HIR "只覺腦中一陣劇痛，金星亂"
                                "冒，猶如有萬條金龍在眼前舞動。\n" NOR, target);
                } else
                {
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
                                           HIR "$n" HIR "只覺得$N" HIR "內力猶如"
                                           "排山倒海一般，怎能抵擋？“哇”的一下吐出一大口鮮血。\n" NOR);
                }
        } else
                msg += CYN "$n" CYN "哈哈一笑，飄身躍開，讓$N"
                       CYN "這一吼全然落空。\n" NOR;

        message_combatd(msg, me, target);
        me->start_busy(2);
        /*
        me->want_kill(target);
        me->kill_ob(target);
        */
        return 1;
}