// pengxin.c 西子捧心

#include <ansi.h>
#include <combat.h>

#define XIN "「" HIM "西子捧心" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int delta;
 
        if( userp(me) && !query("can_perform/yuenv-jian/xin", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("sword", 1) < 200)
                return notify_fail("你的劍術修為不夠，不能施展" XIN "！\n");

        if (me->query_skill("yuenv-jian", 1) < 140)
                return notify_fail("你的越女劍術的修為不夠，不能施展" XIN "！\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的輕功修為不夠，不能施展" XIN "！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠！\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        if( query("gender", me) == "女性" && 
            query("gender", target) == "女性" )
                delta=query("per", target)-query("per", me);
        else
                delta = 0;

        msg = HIG "\n$N" HIG "幽幽一聲長嘆，手中的" + weapon->name() +
              HIG "就如閃電般刺向$n" HIG "的胸口。\n但見劍招輕盈靈動，優美華麗，就"
              "連殺人間也不帶一絲塵俗之氣。\n" NOR;

        if (delta > 0)
                msg += HIY "$n" HIY "只覺得$N" HIY "眼神中隱然透出"
                       "一股冰冷的寒意，心中不禁一顫。\n" NOR;
        else
                delta = 0;

        addn("neili", -180, me);
        ap = (me->query_skill("sword") + me->query_skill("dodge")) / 2;
        dp = target->query_skill("dodge");
        me->start_busy(1);
        if (ap * 7 / 10  + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2) + delta * 50;

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "大吃一驚，慌忙躲避，然而劍"
                                           "氣來的好快，哪裡躲得開？\n只聽$p" HIR
                                           "一聲慘叫，胸口已經被劍氣所傷！\n" NOR);
                if (ap / 2 + random(ap) > dp)
                {
                        damage /= 3;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
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