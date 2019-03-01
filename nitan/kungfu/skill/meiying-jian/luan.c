

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("你只能對戰鬥中的對手使用「亂影劍」。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不對！\n");
                
        if (me->query_skill_mapped("sword") != "meiying-jian")
                return notify_fail("你沒有激發魅影劍法，無法施展。\n"); 

        if ((int)me->query_skill("meiying-jian", 1) < 200)
                return notify_fail("你目前功力還使不出「亂影劍」。\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("你的內力不夠。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        me->add("neili", -200);
        msg = HIM "\n$N" HIM "露出詭異的笑容，忽然身法陡然加快，有如完全鬼影般旋轉，"
              "手中$N" HIM "亂影般激射而出，$n" HIW "只覺魅影圍繞，窒息之極！\n" NOR;

        if (random(10) < 2)
        {
                if (random(10) < 7)me->start_busy(1);
                else
                {
                        me->start_busy(2);
                }               
        }
        
        ap = me->query_skill("dodge") + me->query_skill("force");
        dp = target->query_skill("dodge") + target->query_skill("force");
        
        if (ap * 3 / 4 + random(ap) > dp)
        {
                if (random(3) == 1)target->start_busy(2);
                damage = ap * 2 + random(ap);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100, 
                                           HIR "只見$n" HIR "已被$N" HIR
                                           "刺得體無完膚，血如箭般由全身噴射而出！\n" NOR);
        } else
        {
                msg += HIC "可是$p" HIC "急忙抽身躲開，使$P"
                       HIC "這招沒有得逞。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        return 1;
}

