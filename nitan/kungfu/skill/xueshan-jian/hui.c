#include <ansi.h>
#include <combat.h>

string name() { return HIW "風迴雪舞" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 50)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("xueshan-jian", 1) < 30)
                return notify_fail("你的雪山劍法修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xueshan-jian")
                return notify_fail("你沒有激發雪山劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        //msg = HIC"$N回劍旋舞，劍勢不斷加快，劍氣呼嘯四散，如片片雪花遇風，飄然而出。\n形成一個雪花形旋渦，將$n裹在內裏。\n";
        msg = HIW "$N" HIW "回劍旋舞，一式「風迴雪舞」施出，劍勢連綿不絕，呼"
              "嘯而至，欲圖將$n" HIW "纏裹其中。\n" NOR;

        addn("neili", -30, me);
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "$n" HIR "只覺重重劍影鋪天蓋地向自己撒"
                       "來，頓被攻了個手忙腳亂，不知如何應對。\n"
                       NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，鎮"
                       "定逾恆，全神應對自如。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
