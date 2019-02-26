#include <ansi.h>
#include <combat.h>

#define XIAN "「" HIR "阿鼻道三刀" NOR "」"

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp;

        if( userp(me) && !query("can_perform/badao/san", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");
                
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對！\n");

        if ((int)me->query_skill("badao", 1) < 1000)
                return notify_fail("你霸刀火候不足，無法施展" XIAN "。\n");

        if ((int)me->query_skill("force", 1) < 800)
                return notify_fail("你基本內功修為不夠，無法施展" XIAN "。\n");

        if( query("neili", me)<3000 )
                return notify_fail("你現在真氣不夠，無法施展" XIAN "！\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("你沒有激發霸刀，無法使用" XIAN "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        addn("neili", -3000, me);

        ap=me->query_skill("blade")+me->query_skill("force")+me->query_skill("martial-cognize",1)+query("str", me);
        dp = target->query_skill("dodge") + target->query_skill("force") + target->query_skill("martial-cognize", 1);

        message_combatd(HIW "\n$N" HIW "一聲長歎，似乎看盡凡塵滄桑，事態萬千，持刀而立，遙望天際 ……\n\n", me, target);        

        // 第一刀
        msg = HIY "$N" HIY "踏步向前，施展出阿鼻道三刀之「一刀入魔」，" + weapon->name() + HIY 
              "順勢劈過，狂風驟起，大地迴歸黑暗 ……\n" NOR;

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap * 2 + random(ap);
                msg+=COMBAT_D->do_damage(me,target,WEAPON_ATTACK,damage,300+query("str", me),
                                           HIR "$n" HIR "驚魂未定，竟然不知躲避，被$N"
                                           HIR "一刀劈過，刀氣如體，口吐鮮血，接連後退。\n" NOR);                
        }
        else
        {
                msg += CYN "$n" CYN "飛身一躍，滾在一邊。\n" NOR;
        }

        // 第二刀
        msg += HIY "\n$N" HIY "輕歎，猛然間，手臂一揮，一式阿鼻道三刀之「人間煉獄」已然使出，" + weapon->name() + HIY "長鳴一聲"
               "，劃破黑暗，吹吸間，一道熾熱的白光卷向$n" HIY "，周圍空氣令人窒息。\n" NOR;

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap * 3 + random(ap);
                msg+=COMBAT_D->do_damage(me,target,WEAPON_ATTACK,damage,300+query("str", me),
                                          (: attack1, me, target, damage :));
        }
        else
        {
                msg += CYN "$n" CYN "胡亂施展招式，竟將這招化解。\n" NOR;
        }

        // 第三刀
        msg += HIY "\n$N" HIY "雙眼一紅，力量大增，猛然怒呵一聲，飛天而起，但見天地又重歸黑暗，似乎整個塵世已經"
              "墜入無間地獄般，令人再無半點生念，突然，四周充斥着鬼哭狼嚎的巨響，$N" HIY "卻早已沒了蹤影。\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap * 4 + random(ap);
                msg+=COMBAT_D->do_damage(me,target,WEAPON_ATTACK,damage,350+query("str", me),
                                           (: attack2, me, target, damage :));
                                                           

        }
        else
        {
                msg += CYN "$n" CYN "收攝心神，小心應對，竟將此招化解與無形。\n" NOR;
        }

        me->start_busy(4 + random(4));
        message_combatd(sort_msg(msg), me, target);
        return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

        msg = HIR "$n" HIR "只覺心中一陣淒涼，胸口卻已翻騰不息，説不出的難受。\n" NOR;

        addn("neili", -1*damage/2, target);
        
        return msg;
}

string attack2(object me, object target, int damage)
{
        string msg;

        msg = HIR "$n" HIR "早已十魂失了八魄，正驚疑間，眼前一閃，刀氣透體而過。\n" NOR;

        target->receive_wound("jing", damage / 8, me);
        if (random(4) == 1)target->start_busy(5 + random(5));
        
        return msg;        
}