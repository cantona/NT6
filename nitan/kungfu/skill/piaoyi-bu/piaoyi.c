// piaoyi.c 飄逸步法 靈燕飄逸

#include <ansi.h>
#include <combat.h> 

#define PIAOYI HIG "「靈燕飄逸」" NOR 

inherit F_SSERVER;

void remove_effect(object me, int aamount, int damount);

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int d_count, count, qi, maxqi, skill;

        if( query_temp("piaoyi", me) )
                return notify_fail("你已經在運功中了。\n");

        if ( userp(me) 
         && me->query_skill("piaoyi-bu", 1) < 150
          && !query("can_perform/piaoyi-bu/piaoyi", me) )
                return notify_fail( "你所使用的外功中沒有這樣的功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail( PIAOYI + "只能對戰鬥中的對手使用。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法施展" + PIAOYI + "！\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠，不能使用" + PIAOYI + "！\n");

        if ((int)me->query_skill("dodge") < 150)
                return notify_fail("你的基本輕功還不到家，無法使用" + PIAOYI + "！\n");

        if (me->query_skill_mapped("dodge") != "piaoyi-bu") 
                return notify_fail("你沒有激發飄逸步法，無法使用" + PIAOYI + "！\n");

        msg = HIG "$N" HIG "催動自己的真力運勁於雙腿，使出飄逸步法的絕技" + 
              PIAOYI + HIG "，身形頓時如靈燕一般！\n" NOR;
        
        qi=query("qi", me);
        maxqi=query("max_qi", me);
        skill = (int) (me->query_skill("piaoyi-bu", 1) / 3);
        count = (int)me->query_skill("dodge",1) / 4;
        d_count = (int)me->query_skill("parry",1) / 2;

        if (qi > (maxqi * 0.4))
        {       
                message_combatd(msg, me, target);
                
                addn_temp("apply/dodge", count*2, me);
                addn_temp("apply/parry", -d_count, me);
                set_temp("piaoyi", 1, me);
                me->start_call_out((: call_other, __FILE__, "remove_effect", me, count * 2, d_count :), skill);
                addn("neili", -500, me);
        } else
        {
                msg = HIR "$N" HIR "全力催動真力，試圖將自己的身行移動提高到極限"
                      ", 雙腿骨骼一陣爆響！\n" NOR;
                msg = HIR "$N" HIR "發現自己催動的內力將雙腿的經脈盡數震斷, 再也站立不住, 一頭栽倒在地！\n" NOR;
                message_combatd(msg, me, target);
                set("neili", 0, me);
                addn("max_neili", -10, me);

                me->unconcious();
        }
        return 1;
}

void remove_effect(object me, int aamount, int damount)
{
        if( query_temp("piaoyi", me) )
        {
                addn_temp("apply/dodge", -aamount, me);
                addn_temp("apply/parry", damount, me);
                delete_temp("piaoyi", me);
                tell_object(me, HIG "你的" + PIAOYI + HIG "運功完畢，雙腿一陣痠麻。\n");
        }
}