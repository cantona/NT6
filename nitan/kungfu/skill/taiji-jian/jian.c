// 太□□意

#include <ansi.h>
#include <combat.h>

string name() { return HIM "太□□意" NOR; }

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, fp;
        int xy;

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用太□□意！\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( me->is_busy() )
                return notify_fail("你正忙著呢。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對！\n");

        if ((int)me->query_skill("taiji-jian", 1) < 1000)
                return notify_fail("你太極劍法不夠嫻熟，無法施展" + name() + "。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "！\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("你沒有激發太極劍法，無法使用" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -1000, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        fp = defense_power(target, "parry");

        xy = me->query_skill("tianwei-zhengqi", 1);

        ap = ap + ap*(xy/100<10?10:xy/100)/100;

        damage = damage_power(me, "sword");
        damage = damage + damage*(xy/50<10?10:xy/50)/100;
        damage *= 3;

        //target->start_busy(10);

        message_combatd(sort_msg(HIY "\n$N" HIY "身形一轉，手中" + weapon->name() + HIY "輕靈而出，猶如碧"
                     "波盪漾，蜿蜒起伏，形態飄逸瀟洒之極，頗具" HIC "太□" HIY "之意" HIY "……\n" NOR), me);

        msg = HIM "$N" HIM "將內力灌輸于劍上，呼的一劍抖出，空氣幾欲凝固。\n" NOR;
        if (ap + random(ap / 2) < dp)
                msg += CYN "$n" CYN "眼明手快，斜身閃開。\n" NOR;
        else
        {

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200 + (xy / 2 + random(xy / 2)>500?500:xy / 2 + random(xy / 2)),
                                           (: attack1, me, target, damage :));
        }

        msg += HIM "\n$N" HIM "輕搖" + weapon->name() + HIM "，霎時，劍氣縱橫，流光乍現，令人目不暇接。\n" NOR;
        if (ap + random(ap / 2) < fp)
                msg += CYN "$n" CYN "倒吸一口涼氣，飛身一跳，狼狽地躲過這招。\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200 + (xy / 2 + random(xy / 2)>500?500:xy / 2 + random(xy / 2)),
                                           (: attack2, me, target, damage :));
        }

        me->start_busy(2 + random(3));
        message_combatd(msg, me, target);

        return 1;
}


string attack1(object me, object target, int damage)
{
        string msg;

        msg = HIR "$N" HIR "劍法飄逸無比，令$n" HIR "毫無反應，"
              "竟呆立當場，不守不攻。\n" NOR;

        // if( random(2) != 1 ) return msg;
        //if( target->query_condition("no_perform") ) return msg;

        target->apply_condition("no_perform", 5);

        msg += WHT "$n" WHT "感到氣脈受損，全身力道竟似渙散了一般，全然無法控制。\n" NOR;

        return msg;
}

void remove_effect(object target)
{
        if( !objectp(target) ) return;

        addn_temp("apply/avoid_busy", 90, target);
        addn_temp("apply/reduce_busy", 36, target);
        addn_temp("apply/avoid_weak", 90, target);
        addn_temp("apply/avoid_locked", 90, target);
        tell_object(target, HIR "你的忽視虛弱，忽視忙亂、忽視絕招冷凍能力終于解除封印。\n" NOR);
}

string attack2(object me, object target, int damage)
{
        string msg;

        msg = HIR "$N" HIR "劍法越發凌厲，將$n" HIR "逼得接連後退，"
              "劍光一閃，令$n" HIR "再也無從躲避。\n" NOR;

        if( random(2) != 1 ) return msg;

        addn_temp("apply/avoid_busy", -90, target);
        addn_temp("apply/reduce_busy", -36, target);
        addn_temp("apply/avoid_weak", -90, target);
        addn_temp("apply/avoid_locked", -90, target);
        call_out("remove_effect", 30, target);

        msg += WHT "$n" WHT "感到自身的忽視虛弱，忽視忙亂、忽視絕招冷凍能力被封印。\n" NOR;

        return msg;
}
