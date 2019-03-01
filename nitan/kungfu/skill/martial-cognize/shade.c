// shade.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int lvl,i;
        object env, *inv;
       string *can_perform;

       can_perform=query("can_perform/martial-cognize", me);

       if(!can_perform || 
          !arrayp(can_perform) || 
          !sizeof(can_perform) || 
          member_array("shade",can_perform) == -1
         )
                return notify_fail("你還沒有學會使用﹝天龍之霧﹞！\n");

        if (me->is_busy())
                return notify_fail("你上一個動作還沒有完成，無法使用天龍之霧。\n");

        lvl = (int)me->query_skill("martial-cognize",1);

       if(lvl < 250)
                return notify_fail("你的武學修養不夠高深！\n");

        if( query("jingli", me)<500 )
                return notify_fail("你的精力不夠！\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("你的精力還沒有達到足夠的層次！\n");

       if( query("jing", me) <= 300 )
                return notify_fail("你的精神狀態不好！\n");

       if( query("env/invisibility", me) )
                return notify_fail("你正在施展﹝天龍之霧﹞\n");

       if( time()-query("last_shade_time", me)<600 )
                return notify_fail("你剛使用過﹝天龍之霧﹞不久，還沒有完全恢復過來，先休息一會吧。\n");

       if( environment(me) && query("no_fight", environment(me)) )
                return notify_fail("這裡不能使用﹝天龍之霧﹞!\n");

        addn("jingli", -300, me);
        me->receive_damage("jing", 200);

        message_vision(HIW "$N面色凝重，兩道精光從雙目爆射而出，一陣白色霧氣迅速湧出鼻孔，把自己渾身上下都包圍著，整個人漸漸虛化．．．\n" NOR, me);
                set("env/invisible", 1, me);

       set("last_shade_time", time(), me);
       me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), lvl/5);
       if( me->is_fighting() ) me->start_busy(3);
       return 1;

}
void remove_effect(object me)
{
        delete("env/invisible", me);
        tell_object(me,"你的天龍之霧失效了！\n");
        message_vision(HIW "一陣霧氣突然出現，並且越來越濃，旋即又四散而卻，$N顯身了。\n" NOR,me);
}