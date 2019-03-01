// This program is a part of NITAN MudLIB
// xiyan.c

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIM "吸燄令" NOR; }

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword")
                return notify_fail("你使用的兵器不對，不能使用聖火令法之" + name() + "。\n");

        skill = me->query_skill("shenghuo-ling", 1);

        if (! objectp(weapon2 = query_temp("weapon", target)))
                return notify_fail("對方沒有使用兵器，不能使用聖火令法之" + name() + "。\n");

        if (skill < 140)
                return notify_fail("你的聖火令法等級不夠, 不能使用聖火令法之" + name() + "。\n");

        if (query("max_neili", me) < 1500)
                return notify_fail("你的內力修為不足，不能使用聖火令法之" + name() + "。\n");

        if (query("neili", me) < 300)
                return notify_fail("你的真氣不夠，不能使用聖火令法之" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIM "突然$N" HIM "詭異的一笑，使出聖火令法之吸燄"
              "令，手中" + weapon->name() + HIM "幻出數個小圈"
              "，將$n" HIM "的" + weapon2->name() + HIM "緊緊"
              "纏住。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -240, me);
                msg += HIM "$n" HIM "只見眼前無數寒光顫躍閃動，頓時只感"
                      "頭暈目眩，手腕一麻，手中" + weapon2->name() + HIM
                      "已被$N" HIM "納入懷中！\n" NOR;
                me->start_busy(2);
                weapon2->move(me, 1);
        } else
        {
                addn("neili", -100, me);
                msg += CYN "可是$n" CYN "看破$N" CYN "的企圖，將手中兵"
                      "刃揮舞得密不透風，使得$N" CYN "無從下手。\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}
