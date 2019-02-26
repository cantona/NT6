// pengxin.c 西子捧心

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int delta;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「西子捧心」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( userp(me) && !query("can_perform/yuenv-jian/pengxin", me) )
                return notify_fail("你不會使用「西子捧心」這一絕技！\n");

        if (me->query_dex() < 35)
                return notify_fail("你的身法不夠，目前還不能使用這項絕技！\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你的劍術修為不夠，目前不能使用「西子捧心」！\n");

        if (me->query_skill("yuenv-jian", 1) < 100)
                return notify_fail("你的越女劍術的修為不夠，不能使用這一絕技！\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的輕功修為不夠，無法使用「西子捧心」！\n");
 
        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        if( query("gender", me) == "女性" && 
            query("gender", target) == "女性" )
                delta=query("per", target)-query("per", me);
        else
                delta = 0;

        msg = HIG "$N" HIG "幽幽一聲長歎，手中的" + weapon->name() +
              HIG "就如閃電般刺向$n的胸口。\n" NOR;
        if (delta > 0)
                msg += HIY "$n" HIY "只覺得$N" HIY "眼神中隱然透出"
                       "一股冰冷的寒意，心中不禁一顫。\n" NOR;
        else
                delta = 0;

        addn("neili", -150, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        me->start_busy(2);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword") + delta * 50;
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "$n" HIR "大吃一驚，慌忙躲避，然而劍"
                                           "氣來的好快，哪裏躲得開？\n只聽$p" HIR
                                           "一聲慘叫，胸口已經被劍氣所傷！\n" NOR);
                if (ap / 3 + random(ap) > dp)
                {
                        damage /= 4;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                                   HIC "$n重創之下不禁破綻迭出，$P"
                                                   HIC "見狀隨手刺出" + weapon->name() +
                                                   HIC "，又是一劍！\n" HIR "就聽$p"
                                                   HIR "又是一聲慘叫，痛苦不堪。\n" NOR);
                }
        } else
        {
                msg += HIC "$n" HIC "見狀身形急退，避開了$N"
                       HIC "的無形劍氣的凌厲一擊！\n" NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}