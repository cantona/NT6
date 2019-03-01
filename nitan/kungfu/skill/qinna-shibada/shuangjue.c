// shuangjue.c  拳腿雙絕

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
              int i, j, z, y;
              i = me->query_skill("zhentian-quan",1);
              j = me->query_skill("chuanyun-tui",1);
              z = me->query_skill("xuantian-wuji",1);
              y = (i+j+z)/4;
              

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("拳腿雙絕只能對戰鬥中的對手使用。\n");

               if( objectp(query_temp("weapon", me)) )
               return notify_fail("你必須空手使用「拳腿雙絕」！\n");

        if (me->query_skill_prepared("cuff") != "zhentian-quan"
            || me->query_skill_prepared("leg") != "chuanyun-tui"
            || me->query_skill_mapped("cuff") != "zhentian-quan"
            || me->query_skill_mapped("leg") != "chuanyun-tui")
                return notify_fail("你現在無法使用「拳腿雙絕」進行攻擊！\n");

        if( (int)me->query_skill("zhentian-quan", 1) < 100 )
                return notify_fail("你的震天拳不夠嫻熟，無法施展出拳腿雙絕。\n");

            if( (int)me->query_skill("strike", 1) < 100 )
                return notify_fail("你的拳法不夠嫻熟，無法施展出拳腿雙絕。\n");

          if( (int)me->query_skill("lag", 1) < 100 )
                return notify_fail("你的腿法不夠嫻熟，無法施展出拳腿雙絕。\n");

             if( (int)me->query_skill("force", 1) < 100 )
                return notify_fail("你的內功不夠嫻熟，無法施展出拳腿雙絕。\n");

        if( (int)me->query_skill("chuanyun-tui", 1) < 150 )
                return notify_fail("你的穿雲腿不夠嫻熟，無法施展出拳腿雙絕。\n");
              if( (int)me->query_skill("parry", 1) < 100 )
                return notify_fail("你的招架不夠嫻熟，無法施展出拳腿雙絕。\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 100)

                return notify_fail("你的玄天無極功火候不夠，無法施展出拳腿雙絕。\n");
               if( (int)me->query_dex() < 30 )
                           return notify_fail("你的身法欠佳，無法施展出拳腿雙絕。\n");
               if( (int)me->query_str() < 30 )
                           return notify_fail("你的體魄不足，無法發揮出拳腿雙絕的威力。\n");
               if( (int)me->query_int() < 30 )
                           return notify_fail("你的悟性不夠，無法領悟出拳腿雙絕。\n");
        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力不夠，無法施展出拳腿雙絕。\n");
        if( query("neili", me)<1000 )
                return notify_fail("你的真氣不夠，無法施展出拳腿雙絕。\n");

        message_vision(RED "$N一聲清嘯，拳腳齊施，使出昆侖絕學「拳腿雙絕」迅捷無倫地攻向$n！\n"NOR,me, target);
          addn("neili", -400, me);
                 addn_temp("apply/str", y, me);
                 addn_temp("apply/attack", y, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        addn_temp("apply/str", -y, me);
        addn_temp("apply/attack", -y, me);
        me->start_busy(2);
        return 1;
}