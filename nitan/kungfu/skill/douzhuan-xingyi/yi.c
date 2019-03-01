// yi.c 鬥轉星移

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "鬥轉星移"; }

int perform(object me, object target)
{
        object weapon;
        object *obs;
        object der;
        string msg;
        int ap, dp;
        int damage;
        int i;

        me->clean_up_enemy();
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「鬥轉星移」只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("douzhuan-xingyi", 1) < 100)
                return notify_fail("你的鬥轉星移不夠嫻熟，不會使用絕招。\n");

        if ((int)me->query_skill("shenyuan-gong", 1) < 100)
                return notify_fail("你的神元功修為還不到家，"
                                   "難以運用「鬥轉星移」。\n");

        if( query("neili", me)<60 )
                return notify_fail("你現在真氣不夠，無法使用「鬥轉星移」。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        weapon=query_temp("weapon", target);
        if( weapon && query("skill_type", weapon) == "pin" )
                return notify_fail("對方手裡拿的是一根小小的針，"
                                   "你沒有辦法施展「鬥轉星移」。\n");

        msg = HIM "$N" HIM "運起紫徽心法，內力自氣海穴出，經由"
              "任督二脈奔流而出，巧妙的牽引著$n" HIM "的招式！\n";

        ap = attack_power(me, "parry");
        dp = defense_power(target, "force") +
             target->query_skill("dragon-strike", 1);

        der = 0;
        me->start_busy(2);
        addn("neili", -50, me);
        if (ap > dp * 11 / 10)
        {
                // Success to make the target attack hiself
                msg += HIR "結果$p" HIR "一招擊出，正好打在自己的"
                       "要害上，不禁一聲慘叫，摔跌開去。\n" NOR;
                damage=query("max_qi", target);
                target->receive_damage("qi", damage / 2, me);
                target->receive_wound("qi", damage / 2, me);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                // The enemy has defense
                msg += CYN "然而$p" CYN "內功深厚，並沒有被$P"
                       CYN "這巧妙的勁力所帶動。\n" CYN;
        } else
        if (sizeof(obs = me->query_enemy() - ({ target })) == 0)
        {
                // No other enemy
                msg += HIC "結果$p" HIC "的招式莫名其妙的變"
                       "了方向，竟然控制不住！幸好身邊沒有別"
                       "人，沒有釀成大禍。\n" NOR;
        } else
        {
                string name;
                // Sucess to make the target attack my enemy
                der = obs[random(sizeof(obs))];
                name = der->name();
                if (name == target->name()) name = "另一個" + name;
                msg += HIG "結果$p" HIG "發出的招式不由自主"
                       "的變了方向，突然攻向" + name + HIG "，不禁令" +
                       name + HIG "大吃一驚，招架不迭！" NOR;
        }

        message_combatd(msg, me, target);

        if (der)
        {
                // Target attack my enemy
                for (i = 0; i < 2 + random(3); i++)
                {
                        if (! der->is_busy()) der->start_busy(1);
                        COMBAT_D->do_attack(target,der,query_temp("weapon", target));
                }
        }

        return 1;
}
