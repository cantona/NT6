#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "天脈神劍"; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, skill;
        int n;

        if (! target) target = offensive_target(me);

        if( !query("reborn/times", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if( query("family/family_name", me) != "段氏皇族" 
         && member_array("段氏皇族", query("reborn/fams", me)) == -1 ) 
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( me->is_busy() )
                return notify_fail("你正忙著呢。\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你沒有準備使用六脈神劍，無法施展" + name() + "。\n");

        skill = me->query_skill("six-finger", 1);

        if (skill < 800)
                return notify_fail("你的六脈神劍修為有限，無法使用" + name() + "！\n");

        if (me->query_skill("force", 1) < 1000)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "！\n");

        if( query("max_neili", me)<12000 )
                return notify_fail("你的內力修為不夠,無法施展" + name() + "！\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的真氣不夠，現在無法施展" + name() + "！\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須是空手才能施展" + name() + "！\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");


        msg = HIM "$N" HIM "一聲清嘯，右手五指紛彈，頓覺六脈劍譜已湧上心頭，此起"
              "彼伏、連綿不絕。\n霎時劍氣如奔，連綿無盡的萬道劍氣豁然貫向$n" HIM
              "！\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");

        // 提高20%
        ap = ap + ap / 5 + me->query_skill("martial-cognize", 1) + me->query_skill("jingluo-xue", 1);

        // 有20%幾率施展無BUSY
        if (random(5) != 1) me->start_busy(2 + random(3));

        if ((int)target->query_skill("martial-cognize", 1) >= 2000
            && target->query_skill("dodge", 1) >= me->query_skill("six-finger", 1)
            && random (10) == 1 )
        {
                addn("neili", -2000, me);
                msg += HIY "但見$n" HIY "會心一笑，輕拂衣袖，輕易的躲過這一招！\n"NOR;
        } else
        if (ap + random(ap) > dp)
        {
                damage = damage_power(me, "finger") + me->query_skill("martial-cognize", 1) + me->query_skill("jingluo-xue", 1);
                damage *= 3;
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        damage += damage*n*15/100;
                        msg += HIM"$N"HIM"運用氣脈流轉的輔助，使得天脈神劍傷害更強。\n"NOR;
                }

                addn("neili", -1800, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300 + random(200),
                                           HIR "只聽$n" HIR "一聲慘叫，萬道劍氣已"
                                           "透體而過，傷口處鮮血頓時狂湧，痛苦難當！\n" NOR);
                target->set_weak(5);
                if( !target->is_busy() ) target->start_busy(8);
        } else
        {
                addn("neili", -400, me);
                msg += CYN "$n" CYN "見$N" CYN "來勢洶湧，不敢輕易"
                       "招架，急忙提氣躍開。\n" NOR;
        }

        msg += HIG "\n緊接著，$N" HIG "一聲清嘯，左手五指紛彈，頓覺六脈劍譜已湧上心頭，此起"
              "彼伏、連綿不絕。\n霎時劍氣如奔，連綿無盡的萬道劍氣豁然貫向$n" HIG
              "！\n" NOR;

        // 再發一招
        if ((int)target->query_skill("martial-cognize", 1) >= 2000
            && target->query_skill("dodge", 1) >= me->query_skill("six-finger", 1)
            && random (10) == 1 )
        {
                addn("neili", -600, me);
                msg += HIY "但見$n" HIY "會心一笑，輕拂衣袖，輕易的躲過這一招！\n"NOR;
        } else
        if (ap + random(ap) > dp)
        {
                damage = damage_power(me, "finger") * 3;
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        damage += damage*n*15/100;
                        msg += HIM"$N"HIM"運用氣脈流轉的輔助，使得天脈神劍傷害更強。\n"NOR;
                }

                addn("neili", -800, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300 + random(200),
                                           HIR "只聽$n" HIR "一聲慘叫，萬道劍氣已"
                                           "透體而過，傷口處鮮血頓時狂湧，痛苦難當！\n" NOR);
                target->set_weak(5);
                if( !target->is_busy() ) target->start_busy(8);
        } else
        {
                addn("neili", -400, me);
                if (random(5) != 1)me->start_busy(5);
                msg += CYN "$n" CYN "見$N" CYN "來勢洶湧，不敢輕易"
                       "招架，急忙提氣躍開。\n" NOR;
        }
        message_combatd(msg, me, target);


        return 1;
}
