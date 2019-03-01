// This program is a part of NITAN MudLIB
// xiang.c 龍翔九天

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "龍翔九天"; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「龍翔九天」只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("「龍翔九天」只能空手使用。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為還不夠，無法施展「龍翔九天」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        if( query("qi", me)<800 )
                return notify_fail("你的體力現在不夠！\n");

        if ((int)me->query_skill("dragon-strike", 1) < 150)
                return notify_fail("你的降龍十八掌火候不夠，無法使用「龍翔九天」！\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠，無法使用「龍翔九天」！\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你現在沒有準備使用降龍十八掌，無法使用「龍翔九天」！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "深吸一口氣，跨前一步，雙掌猛然翻滾，"
              "繽紛而出，宛如一條神龍攀蜒于九天之上！\n\n" NOR;

        ap = attack_power(me, "strike") + me->query_str();
        dp = defense_power(target, "parry") + target->query_dex();

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 9;
                msg += HIR "$n" HIR "面對$P" HIR "這排山倒海攻勢，完全"
                       "無法抵擋，唯有退後。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "凝神應戰，竭盡所能化解$P" HIC
                       "這幾掌。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);

        addn("neili", -300, me);
        addn("qi", -100, me);//WhyIdon'tusereceive_damage?
                                // Becuase now I was use it as a cost
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(5));
        addn_temp("apply/attack", -count, me);

        return 1;
}
