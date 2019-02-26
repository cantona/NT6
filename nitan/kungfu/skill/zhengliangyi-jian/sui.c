#include <ansi.h>
#include <combat.h>

#define SUI "「" HIW "玉碎昆岡" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        string pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if( userp(me) && !query("can_perform/zhengliangyi-jian/sui", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(SUI "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，無法施展" SUI "。\n");

        if ((int)me->query_skill("zhengliangyi-jian", 1) < 180)
                return notify_fail("你的正兩儀劍法不夠嫻熟，難以施展" SUI "。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功火候不足，難以施展" SUI "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不足，難以施展" SUI "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" SUI "。\n");

        if (me->query_skill_mapped("sword") != "zhengliangyi-jian") 
                return notify_fail("你沒有激發正兩儀劍法，難以施展" SUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "仰天一聲慘笑，將" + weapon->name() + HIY
              "劍尖指向自己胸口，劍柄斜斜向外，連人帶劍電射而出，直"
              "撲$n" HIY "而去！\n" NOR;
        addn("max_neili", -50, me);

        me->want_kill(target);
        target->kill_ob(me);
        ap = me->query_skill("sword");
        dp = target->query_skill("force");

        if (ap / 2 + random(ap * 3 / 2) > dp)
        {
                me->start_busy(6);
                set("neili", 0, me);
                addn("max_neili", -random(50), me);
                damage = 0;

                if (ap < dp * 3 / 4 &&
                   query("max_neili", me)<query("max_neili", target)*3/4 )
                {
                        msg += HIY "可是$n" HIY "一聲冷哼，飛身閃開來招，又順勢轉身一"
                               "掌拍向$N" HIY "面門。\n" NOR + HIR "只聽“喀嚓”一聲"
                               "，$n" HIR "那掌正好打在$N" HIR "頭頂，$N" HIR "哀嚎一"
                               "聲，軟軟的癱倒。\n" NOR;
                        message_combatd(msg, me, target);
                        me->set_temp("die_reason","使用一招玉碎昆岡，拼命不成，反被"
                                     + target->name() + "擊斃");
                        me->die(target);
                        return 1;
                } else
                if (ap > dp &&
                   query("max_neili", me)>query("max_neili", target) )
                {
                        msg += HIR "$n" HIR "眼見$N" HIR "來勢如此兇悍，這一招決計無"
                               "法抵擋，駭怖達於極點，竟致僵立，束手待斃。\n只聽“噗"
                               "嗤”一聲，" + weapon->name() + HIR "已然透過$n" HIR
                               "前胸而入，噴出一股血雨。\n" NOR;
                        message_combatd(msg, me, target);
                        target->set_temp("die_reason","被"+me->name()+"使一招玉"
                                         "碎昆岡刺死了");
                        target->die(me);
                        return 1;
                } else
                if (ap / 2 + random(ap * 2 / 3) > dp)
                {
                        msg += HIR "$n" HIR "眼見$N" HIR "來勢如此兇悍，只覺這一招決"
                               "計無法抵擋，駭怖達於極點，慌亂之中一掌猛拍而出，擊\n"
                               "向$N" HIR "面門，竟也是同歸於盡的招數。只聽“噗嗤”一"
                               "聲，" + weapon->name() + HIR "已然透過$n" HIR "前胸，"
                               "噴出一股血雨。\n同時$n" HIR "那一掌也正好打在$N" HIR
                               "頭頂，聽得“喀嚓”一聲，$N" HIR "頭蓋骨完全碎裂，軟軟"
                               "的癱倒。\n" NOR;
                        message_combatd(msg, me, target);
                        me->set_temp("die_reason","使用一招玉碎昆岡與"+
                                     target->name() + "同歸於盡了");
                        target->set_temp("die_reason","被"+me->name()+"使一招玉"
                                         "碎昆岡，兩人一塊去見了黑白無常");
                        target->die(me);
                        me->die();
                        return 1;
                } else
                {
                        target->start_busy(2 + random(6));
        
                        damage = ap + (int)me->query_skill("force");
                        damage = damage / 2 + random(damage);

                        if( arrayp(limbs=query("limbs", target)) )
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "要害";
                        pmsg = HIR "$n" HIR "眼見$N" HIR "來勢如此兇悍，只覺這一招決"
                               "計無法抵擋，急忙飛身閃避，然而只聽“嗤啦”一聲，那\n"
                               "柄" + weapon->name() + HIR "已然刺穿" + limb + HIR "，"
                               "噴出一股血雨。\n" NOR;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage,
                               150, pmsg);
                }
        } else 
        {
                me->start_busy(8);
                msg += HIY "可是$n" HIY "早已料到$N"
                       HIY "有此一着，身形急動，躲開"
                       "了這一殺着。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}