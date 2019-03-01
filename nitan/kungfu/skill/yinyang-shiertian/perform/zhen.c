#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return HIW "鎮陰陽" NOR; }


int perform(object me, object target)
{
        string msg;
        int lvl;
        int ap, dp, dp1;
        int sub, damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+ "只能空手使用。\n");

        if (me->query_skill_mapped("force") != "yinyang-shiertian")
                return notify_fail("你沒有激發陰陽九轉十二重天為特殊內功，無法使用" +name()+ "。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你的真氣不夠，無法施展" +name()+ "！\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為還不足以使出" +name()+ "。\n");

        if ((int)me->query_skill("force") < 500)
                return notify_fail("你的內功火候不夠，難以施展" +name()+ "！\n");

        if ((lvl = (int)me->query_skill("yinyang-shiertian", 1)) < 500)
                return notify_fail("你的陰陽九轉十二重天還不夠熟練，無法使用" +name()+ "！\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        message_combatd(HIM "\n$N" HIM "運起陰陽九轉十二重天，左手" HIB "陰"
                     HIM "，右手" HIR "陽" HIM "，澎湃的內勁由體內而發，"
                     HIM "以排山倒海之勢卷向$n" HIM "！\n" NOR, me, target);

        ap = attack_power(me, "force");

        sub = 0;
        dp1 = 0;

        if (target->query_skill_mapped("force") == "yinyang-shiertian")
        {
                sub = 3;
                dp1 = target->query_skill("yinyang-shiertian", 1);
        } else
        if (target->query_skill_mapped("force") == "taixuan-gong")
        {
                sub = 3;
                dp1 = target->query_skill("taixuan-gong", 1) / 2;
        } else
        if (target->query_skill_mapped("force") == "taiji-shengong")
        {
                sub = 3;
                dp1 = target->query_skill("taiji-shengong", 1) / 2;
        }else
        if (target->query_skill_mapped("force") == "jiuyin-shengong")
        {
                sub = 1;
                dp1 = target->query_skill("jiuyin-shengong", 1);
        }else
        if (target->query_skill_mapped("force") == "jiuyang-shengong")
        {
                sub = 2;
                dp1 = target->query_skill("jiuyang-shengong", 1);
        }

        //第一招：陰

        dp = defense_power(target, "dodge");

        if (sub == 1 || sub == 3)
                dp += dp1;

        message_combatd(HIB "\n$N" HIB "左掌往前一推，陰寒無比的真氣洶湧而出，"
                     "似乎能連空氣都一起凍住！\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "force")*10;
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(20),
                                          HIB "$n" HIB "但見$N" HIB "左掌已攻出，"
                                          HIB "正欲反擊。突然間胸口一震，不禁暗暗叫苦，"
                                          HIB "胸口處一股寒氣升起，全身都被凍僵了。\n" NOR);
                target->start_busy(3 + random(lvl / 500));
        } else
        {
                msg = CYN "$n" CYN "見$P" CYN "來勢洶湧，不敢輕易抵"
                      "擋，連忙飛身騰挪，躲閃開來。\n" NOR;
        }

        message_combatd(msg, me, target);

        //第二招：陽

        dp = defense_power(target, "parry");

        if (sub == 2 || sub == 3)
                dp += dp1;

        message_combatd(HIR "\n$N" HIR "右手金光萬道，灼熱的真氣澎湃激盪，"
                     HIR "所到之處散發著一股焦臭的味道！\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "force")*10;
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(40),
                                          HIR "$n" HIR "急忙抽身後退，忽然金光暴漲，"
                                          HIR "只見$n" HIR "跌跌撞撞向後連退數步，伏倒"
                                          "在地。須眉、衣衫都發出一股焦臭。\n" NOR);
        } else
        {
                msg = CYN "可是$n" CYN "看透$P" CYN "此招之中的破綻，鎮"
                      "定逾恆，應對自如。\n" NOR;
        }

        message_combatd(msg, me, target);

        me->start_busy(3 + random(4));
        addn("neili", -500-random(200), me);
        return 1;
}
