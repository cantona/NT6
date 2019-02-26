#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "九轉乾坤" NOR; }

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl, damage;
        int i, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能對戰鬥中的對手使用。\n");

        if( query("neili", me)<900 )
                return notify_fail("你的真氣不夠，無法施展" +name()+ "！\n");

        if( query("max_neili", me)<9000 )
                return notify_fail("你的內力修為還不足以使出" +name()+ "。\n");

        if ((int)me->query_skill("force") < 900)
                return notify_fail("你的內功火候不夠，難以施展" +name()+ "！\n");

        if ((lvl = (int)me->query_skill("yinyang-shiertian", 1)) < 810)
                return notify_fail("你的陰陽九轉十二重天還不夠熟練，無法使用" +name()+ "！\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        message_combatd(HIM "\n$N" HIM "運起陰陽九轉十二重天，彷彿九天神龍翱翔天際，"
                     HIM "正是無上絕學" +name()+ HIM "！\n" NOR, me, target);

        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge") + target->query_skill("yinyang-shiertian", 1);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                message_combatd(HIW "\n$N" HIW "身若游龍，挾風雷之力，從空中向$n"
                                HIW "猛撲下來！\n" NOR, me, target);

                if (ap * 3 / 2 + random(ap) > dp)
                {
                        damage = damage_power(me, "force")*10;
                        if( query_temp("weapon", me) )
                        {
                                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, (i + 1) * 10 ,
                                                          HIR "結果$n" HIR "躲閃不及，$N" HIR
                                                          "的內勁已破體而入，$n喉頭一甜，噴出一大"
                                                          "口鮮血。\n" NOR);
                        } else
                        {
                                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, (i + 1) * 10,
                                                          HIR "結果$n" HIR "躲閃不及，$N" HIR
                                                          "的內勁已破體而入，$n喉頭一甜，噴出一大"
                                                          "口鮮血。\n" NOR);
                        }
                } else
                {
                        msg = CYN "$n" CYN "氣凝雙臂，奮力招架，將"
                              "$N" CYN "的內勁卸掉。\n" NOR;
                }

                message_combatd(msg, me, target);

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
        }

        me->start_busy(2 + random(3));
        addn("neili", -1000-random(1000), me);
        return 1;
}

