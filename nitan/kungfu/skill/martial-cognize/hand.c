// hand.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
       int lvl;
       string *can_perform;

       can_perform=query("can_perform/martial-cognize", me);

       if(!can_perform || 
          !arrayp(can_perform) || 
          !sizeof(can_perform) || 
          member_array("hand",can_perform) == -1
         )
                return notify_fail("你還沒有學會使用［天龍之手］！\n");

        if (me->is_busy())
                return notify_fail("你上一個動作還沒有完成，無法使用天龍之手。\n");

        lvl = (int)me->query_skill("martial-cognize",1);

       if(lvl < 250)
                return notify_fail("你的武學修養不夠高深！\n");

        if( query("jingli", me)<500 )
                return notify_fail("你的精力不夠！\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("你的精力還沒有達到足夠的層次！\n");

       if( query("jing", me) <= 300 )
                return notify_fail("你的精神狀態不好！\n");

        if( !target || !target->is_character() )
                return notify_fail("你要對誰使用［天龍之手］？\n");

        if( target->is_corpse() )
                return notify_fail("來不及了，只有活人才能救醒。\n");

       if(me->is_fighting() || target->is_fighting())
                return notify_fail("戰鬥中不能使用［天龍之手］！\n");

        addn("jingli", -400, me);
        me->receive_damage("jing", 250);

       if (target == me)
                message_vision( HIY "$N雙手交疊貼在額頭, 閉上眼睛緩緩低吟...\n" NOR, me);
        else
                message_vision( HIY "$N一手放在$n的天靈蓋上, 一手貼在$n的後心, 閉上眼睛緩緩低吟...\n" NOR, me, target);
        message_vision( HIY "$N臉上綻放出嬰孩般的笑容，似乎正處身於西方極樂世界...\n" NOR, target);

       if( query("jing", target)<1 )
                set("jing", 1, target);
       if( query("max_jing", target)<1 )
                set("max_jing", 1, target);

       if( query("qi", target)<1 )
                set("qi", 1, target);
       if( query("eff_qi", target)<1 )
                set("eff_qi", 1, target);

        if(! living(target))
                target->revive();

       target->remove_all_killer();
        return 1;
}