// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIG "天地情長" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;
        int cost;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("你沒有激發玉簫劍法，難以施展" + name() + "。\n");

        skill = me->query_skill("yuxiao-jianfa", 1);

        if (skill < 150)
                return notify_fail("你玉簫劍法等級不夠，難以施展" + name() + "。\n");

        if( query("neili", target)<300 )
                return notify_fail("看樣子對方真氣並不充沛，無需運用" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIG "$N" HIG "手中的" + weapon->name() + HIG "倏的刺出，捲起一陣"
              "陣氣旋，不住的往裏收縮。\n" NOR;

        ap = attack_power(me, "sword") +
             me->query_skill("chuixiao-jiafa", 1);
        dp = defense_power(target, "force") +
             target->query_skill("chuixiao-jiafa", 1);

        if (ap > dp || ap / 2 + random(ap) > dp)
        {
                addn("neili", -500, me);
                msg += HIM "$p" HIM "頓覺$P" HIM "的內力隱藏在一個個氣旋中，難"
                       "以捉摸去處，只能強運內力抵消。\n" NOR;
                cost = 500 + (ap - dp) * 3 / 2;
                if( cost>query("neili", target) )
                        cost=query("neili", target);
                addn("neili", -cost, target);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -120, me);
                msg += HIC "可是$p" HIC "心神安定，絲毫沒有受到困惑。\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}