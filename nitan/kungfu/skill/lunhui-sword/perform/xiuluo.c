#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "修羅劍神" NOR; } 

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        string sexs;
         
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("lunhui-sword", 1) < 500)
                return notify_fail("你的六道輪回劍修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("你沒有激發六道輪回劍，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("你沒有激發六道輪回劍，難以施展" + name() + "。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        sexs=query("gender", me) == "男性"?"修羅神般威武":"修羅女神般曼妙多姿";
        msg = HIR "$N" HIR "負劍而立，剎那間，劍氣環繞，形態飄逸之極，猶如傳說中的" + sexs + "。猛然間，$N" HIR 
              "手中" + weapon->name() + HIR "化出一道劍光，但見一道無形劍氣奔向$n" HIR "，竟無一絲預兆。\n" NOR;

        ap = attack_power(me, "sword"); 
        dp = defense_power(target, "parry");
        
        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage *= 3;
                addn("neili", -2000, me);
                me->start_busy(2 + random(4));
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 400,
                                           HIR "只聽$n" HIR "一聲慘叫，$N" HIR +
                                           weapon->name() + HIR "劍光一閃，一道劍氣嵌"
                                           "入$p" HIR "體內尺許，帶出一蓬血雨。\n"
                                           NOR);
                if (random(3) == 1)
                {
                        target->receive_damage("jing", damage / 40, me);
                        target->receive_wound("jing", damage / 80, me);
                        target->start_busy(3 + random(4));
                        msg = msg + target->name() +  HIM "突然感覺到頭暈木眩，看來是受到了修羅劍氣的影響。\n" NOR;
                }
        } else
        {
                addn("neili", -1000, me);
                me->start_busy(4);
                msg += CYN "$n" CYN "見$P" CYN "來勢洶湧，不敢輕易抵"
                       "擋，連忙飛身騰挪，躲閃開來。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        return 1;
}