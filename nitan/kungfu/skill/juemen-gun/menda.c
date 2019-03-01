// menda.c  「絕棍悶打」
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

inherit F_SSERVER;
#define PNAME "「"+HIC"絕"NOR+HIG"棍"NOR+HIY"悶"NOR+HIR"打"NOR+"」"
int perform(object me, object target)
{
        int damage;
        string msg;
        int flag;
        object weapon;
        string fskill,sskill,bskill,pfname,pskill;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname) )
   return notify_fail("你所使用的外功中沒有這種功能。\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"只能對戰鬥中的對手使用。\n");

                if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對。\n");

        bskill = "club";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(bskill, 1) < 188 )
                return notify_fail("你的"+to_chinese(fskill)+"太菜，使不出"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 188 )
                return notify_fail("你的"+to_chinese(sskill)+"不夠熟練，不會使用"+PNAME+"。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力修為還不夠高。\n");

        msg = HIW "$N突然反身疾退，$n"HIW"正疑惑發愣間，卻見$N驟然轉身，施展出「"+HIC"絕"NOR+HIG"棍"NOR+HIY"悶"NOR+HIR"打"NOR+"」，"+HIW"左右上下揮舞遊走間，漫天杖影已壓向傻不楞登的$n"HIW"。\n"NOR;

        if( random(query("combat_exp", me))>query("combat_exp", target)/5 )
        {
                me->start_busy(1);
                target->start_busy(random(8));

                damage= (int)me->query_skill(bskill, 1)*5;
                damage = damage + random(damage);

                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/2);
                addn("neili", -500, me);
                msg += HIR"
$n只見漫天都是杖影，根本無從招架，只有挨打的份兒，結果每一杖都被打中，直打得滿頭血包、渾身血條，且五臟六腑亦被重創，鮮血自嘴角汩汩流個不休，眼看就要摔暈在地！！！\n"NOR;
        } else
        {
                me->start_busy(1);
                msg += HIG"可是$p看破了$P的企圖，急忙報頭鼠竄般閃在了一邊。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

int help(object me)
{
        write(WHT"\n絕門棍之絕棍悶打："NOR"\n");
        write(@HELP

        使用功效：
                損傷對方氣血
                遲滯對方出手

        出手要求：
                絕門棍188級
                基本杖法188級
                內力500
HELP
        );
        return 1;
}
