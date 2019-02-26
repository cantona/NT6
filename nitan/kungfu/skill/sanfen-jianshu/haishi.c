// haishi.c 海市蜃樓

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

        if( userp(me) && !query("can_perform/sanfen-jianshu/haishi", me) )
                return notify_fail("你不會使用「海市蜃樓」這一絕技！\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("「海市蜃樓」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("sword", 1) < 150)
                return notify_fail("你的劍術修為不夠，目前不能使用「海市蜃樓」！\n");

        if (me->query_skill("sanfen-jianshu", 1) < 150)
                return notify_fail("你的三分劍術的修為不夠，不能使用這一絕技！\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的輕功修為不夠，無法使用「海市蜃樓」！\n");
 
        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "狂喝一聲，手中" + weapon->name() +
              HIW "將到之際，突然圈轉，使出三分劍術的獨得之祕"
              "「海市蜃樓」，一招之中\n又另藴涵三招，招式繁複狠"
              "辣，劍招虛虛實實，霍霍劍光徑直逼向$n"
              HIW "！\n\n" NOR;

        addn("neili", -150, me);
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        
        me->start_busy(1 + random(2));
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "$n" HIR "完全無法辨清虛實，只感一陣觸心的刺痛，一聲慘叫，已被$N"
                                           HIR "凌厲的劍招刺中。\n" NOR);
                if (ap / 3 + random(ap) > dp)
                {
                        damage /= 2;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                                   HIR "\n$N" HIR "見$n" HIR "重創之下不禁破綻迭出，"
                                                   HIR "冷笑一聲，手中" + weapon->name() +
                                                   HIR "揮灑，又攻出一劍，正中$p" HIR "胸口。\n" NOR);
                }
        } else
        {
                msg += HIC "$n" HIC "見狀身形急退，避開了$N"
                       HIC "凌厲的攻擊！\n" NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
