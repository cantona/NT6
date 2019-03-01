#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "六脈歸宗"; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap,dp;
        int n;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("六脈歸宗只能對戰鬥中的對手使用。\n");

        if (me->query_skill_mapped("finger") != "six-finger")
                return notify_fail("你沒有激發六脈神劍，無法施展「六脈歸宗」。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用六脈歸宗！\n");

        if( (int)me->query_skill("six-finger", 1) < 200 )
                return notify_fail("你的六脈神劍不夠嫻熟，不會使用六劍歸宗。\n");

        if( query("max_neili", me)<8000 )
                return notify_fail("你現在內力不夠深厚，不能使用六劍齊發。\n");

        if( query("neili", me)<1500 )
                return notify_fail("你現在內力太弱，不能使用六劍歸宗！\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你沒有準備使用六脈神劍，無法施展「六脈歸宗」。\n");

        if( !living(target) )
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY"$N使出六脈神劍最強絕技『六脈歸宗』，真氣急運九大周天，內力洶湧滂湃，\n"
              HIR"剎時間數股熾熱剛猛的劍氣自指中射出！！無數迅雷疾風相互沖撞激之際，\n"
              HIW"竟然匯集成一束凌厲無匹的劍柱，宛如一條白色巨蟒,閃電般疾射向$n！！！\n"NOR,

        ap = attack_power(me, "finger") + me->query_skill("force") + me->query_str()*10;;
        ap+= random(1+query("jiali", me)/2);

        dp = defense_power(target, "dodge") + target->query_skill("force") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                if (! target->is_busy())
                        target->start_busy(2 + random(2));

                damage = damage_power(me, "finger");
                damage+=query("jiali", me)*2;
                damage+=query("jianu", me)*(10+random(20));
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        msg += HIM"$N"HIM"運用氣脈流轉的輔助，使得六脈歸宗傷害更強。\n"NOR;
                        damage += damage*n*15/100;
                }

                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                target->receive_damage("jing", damage,me);
                target->receive_wound("jing", damage/2,me);
                addn("neili", -1000, me);

                if( damage < 20 ) msg += HIY"結果$n受到$N的劍氣擊中，悶哼一聲。\n"NOR;
                else if( damage < 40 ) msg += HIY"結果$n被$N的劍氣擊中，「嘿」地一聲退了兩步。\n"NOR;
                else if( damage < 80 ) msg += RED"結果$n被$N的劍氣擊中，胸口有如受到一記重錘，連退了五六步！\n"NOR;
                else msg += HIR"結果$n被$N的劍氣擊中，口中[哇]的吐出一口鮮血，身子如稻草人一般向後飛出丈許！！\n"NOR;

        } else
        {
                me->start_busy(3);
                msg += CYN"可是$p看破了$P的招式，身子微微一閃已經避開了$P的『六脈歸宗』！\n"NOR;
        }
        message_vision(msg, me, target);

        return 1;
}

