// Code of ShenZhou
//By haowen  1/15/1999 

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name("雪蠶絲", ({"xuecan si", "can si","cansi"}));
        set_weight(80);
        set_max_encumbrance(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
         set("long", "這是一根雪蠶絲，是星宿海旁的雪蠶所吐之絲。雪蠶形體遠較冰蠶為小，也無毒性，
吐出來的蠶絲卻韌力大得異乎尋常，一根單絲便已不易拉斷。\n");
                set("unit", "根");
                set("value", 0);
                set("busy_source", random(5)+1);
        }
}
void init()
{
        add_action("do_shou", "shou");
        add_action("do_shou", "catch");
//        add_action("do_fang", "fang");
//      add_action("do_fang", "release");
}
int do_shou(string arg)
{
        object  env,*inv,target,ob,me=this_player();
        int i;
        ob=this_object();
        env=environment(me);
        inv=all_inventory(env);
        for (i=0;i<sizeof(inv);i++){
                if (inv[i]==me) continue;
                if(!me->visible(inv[i])) continue;
                if( query("id", inv[i]) == arg )
                        target=inv[i];
                }
        if (!target) 
                return notify_fail("你想收誰？\n");
        
        if(target==me)
                return notify_fail("你不能收自己！\n");

//      if(!userp(target))
//              return notify_fail("你只能收玩家！\n");
        
        if(me->is_busy())
                return notify_fail("你上一個動作還沒有完成！\n");

        if(!me->is_fighting() || !target->is_fighting() || !living(target))
                return notify_fail("你必須在戰鬥中才能使用雪蠶絲！\n");

        if(me->query_skill_mapped("throwing") != "feixing-shu")
                return notify_fail("你不激發飛星術，無法掌握雪蠶絲的使用方法。\n");

        if(me->query_skill("feixing-shu",1)<30)
                return notify_fail("以你現在的飛星術功力恐怕用不了雪蠶絲！\n");

        if(target->is_busy())
                return notify_fail(query("name", target)+"正自顧不暇，放手攻擊吧！\n");
   
        message_vision( HIY "$N狂笑幾聲，手中似乎有什麼東西向$n撒去。\n" NOR,me,target);
        if(random(me->query_skill("feixing-shu",1)) > random(target->query_skill("dodge",1)))
                {
                 tell_object(target,HIR "你忽然覺得一條細線纏上全身，手腳都已經不受控制！\n" NOR);
                 tell_object(me,HIG "你手中一緊，心中暗喜，看來已經得手了！\n" NOR);
                 target->start_busy(query("busy_source", ob));
//                 me->start_busy(1);
                }
        else {
                message_vision(HIY "$n閃身一躍，避開了$N手中的東西！\n" NOR,me,target);
                tell_object(me,HIG "你趕緊反手一扣，收回了雪蠶絲。\n" NOR);
                me->start_busy(2);
             }          
        addn("neili", -50, me);
        return 1;
}

