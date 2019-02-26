// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;

#define XUAN "「" HIW "太玄激勁" NOR "」"
 
int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i;
        object weapon;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/taixuan-gong/xuan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(XUAN "只能對戰鬥中的對手使用。\n");
        
        if( query("neili", me)<800 )
                return notify_fail("你的真氣不夠，無法施展" XUAN "！\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為還不足以使出" XUAN "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候不夠，難以施展" XUAN "！\n");

        if ((lvl = (int)me->query_skill("taixuan-gong", 1)) < 240)
                return notify_fail("你的太玄功還不夠熟練，無法使用" XUAN "！\n");

        // 未學會如何駕御兵器只能激發為拳腳施展 太玄激勁
        if( !query("can_learned/taixuan-gong/enable_weapon", me) )
        {
             weapon=query_temp("weapon", me);
             if (objectp(weapon))
                     return notify_fail("你還沒有學會如何利用太玄功駕御兵器，這招只能空手施展！\n");

             if (me->query_skill_mapped("unarmed") != "taixuan-gong"
                 || me->query_skill_prepared("unarmed") != "taixuan-gong")
                       return notify_fail("你沒有準備太玄功，無法使用" XUAN "。\n");

        }
        else // 已經學會利用太玄功駕御兵器
        {
             weapon=query_temp("weapon", me);
             // 當沒有持武器時判斷施展該招需要準備為拳腳
             if (! objectp(weapon))
             {
                    if (me->query_skill_mapped("unarmed") != "taixuan-gong"
                        || me->query_skill_prepared("unarmed") != "taixuan-gong")
                              return notify_fail("你沒有準備太玄功，無法使用" XUAN "。\n");
             }          
             // 手持有武器必須為刀或者劍
             else if( objectp(weapon) && query("skill_type", weapon) != "sword"
                       && query("skill_type", weapon) != "blade" )
                              return notify_fail("你使用的武器不對，無法施展" XUAN "。\n");

             if (objectp(weapon) && me->query_skill_mapped("sword") != "taixuan-gong"
                  && query("skill_type", weapon) == "sword" )
                              return notify_fail("你還沒有激發太玄功，無法施展" XUAN "。\n");
             
             else if( objectp(weapon) && query("skill_type", weapon) == "blade"
                      && me->query_skill_mapped("blade") != "taixuan-gong")
                              return notify_fail("你還沒有激發太玄功，無法施展" XUAN "。\n");                              
                         
        }
        if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "\n霎時間$N" HIW "只覺思緒狂湧，當即閉上雙眼，再不理睬$n"
              HIW "如何招架，只管施招攻出！此時俠客島石壁上的千百種招"
              "式，轉眼已從$N" HIW "心底傳向手足，盡數向$n" HIW "襲去！\n" NOR;

        message_combatd(sort_msg(msg), me, target);
        
        addn("neili", -600, me);
        addn_temp("apply/damage", lvl, me);
        addn_temp("apply/unarmed_damage", lvl, me);
        addn_temp("apply/attack", lvl, me);

        for (i = 0; i < 12; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                if (! objectp(weapon))
                COMBAT_D->do_attack(me, target, 0, i * 2);
                else
                COMBAT_D->do_attack(me, target, weapon, i * 2);
        }
        addn_temp("apply/unarmed_damage", -lvl, me);
        addn_temp("apply/attack", -lvl, me);
        addn_temp("apply/damage", -lvl, me);
        me->start_busy(2 + random(5));
        return 1;
}
