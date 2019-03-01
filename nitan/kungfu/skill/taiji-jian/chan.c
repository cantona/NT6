// This program is a part of NITAN MudLIB
// chan.c 纏字訣

#include <ansi.h>

string name() { return "纏字訣"; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「" + name() + "」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("必須拿劍才能施展「" + name() + "」。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if( query("neili", me)<query("max_neili", me)/50 )
                return notify_fail("你的內力不足以施展「" + name() + "」。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 100)
                return notify_fail("你的太極神功火候不夠，難以施展「" + name() + "」。\n");

        if (me->query_skill("taiji-jian", 1) < 100)
                return notify_fail("你的太極劍法不夠嫻熟，不會使用「" + name() + "」。\n");

        msg = HIG "$N使出太極劍法「纏」字訣，先是連遞數個虛招企圖擾亂$n的攻勢。\n"
              HIG "忽然手中" + weapon->name() + HIG "劃出一個個圓圈，神在劍先，"
              HIG "綿綿不絕，便如撒出了一張大網，逐步向$n收緊。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap * 4 / 3) > dp)
        {
                addn("neili", -query("max_neili", me)/50, me);
                msg += HIC "\n結果太極劍意散發出的細絲越積越多，似是積成了一團團絲棉，將$p緊緊裹了起來！\n" NOR;
                target->start_busy(ap / 80 + 3);
                me->start_busy(1);
        } else
        {
                addn("neili", -query("max_neili", me)/80, me);
                msg += HIY "\n可是$p看破了$P的企圖，縱身一躍，已逃出圈外。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

int help(object me)
{
        write(WHT"\n太極劍「纏字訣」："NOR"\n");
        write(@HELP
        太極劍意圓轉不斷，連綿不絕，臨敵人之際以意馭劍，使出「纏」字訣每發
        一招，便似放出一條細絲，纏住對手，千變萬化，無窮無盡，使其無法動作，
        並且可以自動不斷連續發出，直至擊敗對手。

        要求：  最大內力 1000 以上；
                內力 500 以上；
                太極劍等級 100 以上；
                技法太極劍為招架；
                並未設制打不還手。
HELP
        );
        return 1;
}