// This program is a part of NITAN MudLIB
// yi.c 大挪移

#include <ansi.h>

inherit F_SSERVER;

string name() { return "大挪移"; }

int perform(object me, object target)
{
        object weapon;
        object *obs;
        object der;
        string msg;
        int ap, dp;
        int damage;
        int level;
        int i;

        me->clean_up_enemy();
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「大挪移」只能對戰鬥中的對手使用。\n");

        if ((level = (int)me->query_skill("qiankun-danuoyi", 1)) < 50)
                return notify_fail("你的乾坤大挪移還沒有修煉到第二層，無法施展大挪移。\n");

        if (query("neili", me) < 400)
                return notify_fail("你現在真氣不夠，無法使用「大挪移」。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIM "$N" HIM "招數忽然的一變，摹可明方，內力四處回旋，無形中牽引著$n"
              HIM "的招式！\n";

        ap = attack_power(me, "parry");
        dp = defense_power(target, "dodge");

        if (level >= 300)
        {
                // layer 7 force
                ap += level;
        }

        if (ultrap(target))
                dp += target->query_skill("matrial-cognize", 1);

        der = 0;
        me->start_busy(2);
        addn("neili", -350, me);
        if (ap / 2 + random(ap / 2) > dp)
        {
                // Success to make the target attack hiself
                msg += HIR "結果$p" HIR "一招擊出，正好打在自己的"
                       "要害上，不禁一聲慘叫，摔跌開去。\n" NOR;
                // damage = target->query("max_qi");
                damage = damage_power(me, "parry");
                damage+= query("jiali", me);
                damage *= 2;
                target->receive_damage("qi", damage, me);
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
                string pname;
                // Sucess to make the target attack my enemy
                der = obs[random(sizeof(obs))];
                pname = der->name();
                if (pname == target->name()) pname = "另一個" + pname;
                msg += HIG "結果$p" HIG "發出的招式不由自主"
                       "的變了方向，突然攻向" + pname + HIG "，不禁令" +
                       pname + HIG "大吃一驚，招架不迭！" NOR;
        }

        message_combatd(msg, me, target);

        if (der)
        {
                // Target attack my enemy
                for (i = 0; i < 2 + random(3); i++)
                {
                        if (! der->is_busy()) der->start_busy(2);
                        COMBAT_D->do_attack(target, der, query_temp("weapon", target));
                }
        }

        return 1;
}
