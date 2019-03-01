 // duoming.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "奪命銀龍"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail( "奪命銀龍只能在戰鬥中使用\n");


        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");


        if (me->query_skill("force") < 150)
                return notify_fail("你的內功的修為不夠，不能使用「奪命銀龍」！\n");

        if (me->query_skill("yinlong-bian", 1) < 150)
                return notify_fail("你的銀龍鞭修為不夠，目前不能使用「奪命銀龍」！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法使用「奪命銀龍」！\n");

        if (me->query_skill_mapped("whip") != "yinlong-bian")
                return notify_fail("你沒有激發銀龍鞭，不能使用「奪命銀龍」！\n");

        msg = HIB "突然之間，" HIB "$N" HIB "身形一閃一晃，疾退數丈,"+ weapon->name() +
              HIB "從右肩急甩向後，陡地"
              HIB "鞭頭擊向\n" HIB "$n" HIB "面門。" HIB "$N" HIB "本來與"
              HIB "$n" HIB "相隔十丈有余,但"+ weapon->name() +
              HIB "說到便到，正如天"
              HIB "外\n遊龍，矢矯而至。！\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");
        attack_time = 5;
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "結果$p" HIR "被$P" HIR
                       "攻了個措手不及，目接不暇，疲于奔命！\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                attack_time += random(ap / 90);
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "鞭勢狠辣，心下凜然，凝神應付。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        if (attack_time > 10)
                attack_time = 10;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(5));
        return 1;
}