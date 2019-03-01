// qianqianbiao.c                       心有千千鏢

#include <weapon.h>
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("心有千千鏢" NOR, ({"biao"}));
        set_weight(50);

        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "枚");
                set("long", "這是一枚四川唐門秘制的暗器，威力無比。\n");
                set("value", 0);
        }
        setup();
}

void init()
{
        add_action("do_perform","use");
}

int do_perform(string arg)
{
        object me, target;
        string msg;

        me = this_player();
        
        me->clean_up_enemy();
        target = me->select_opponent();

        if ( !arg || arg != "qian")
                return 0;
        
        if ( !(me->is_fighting()) )
                return notify_fail("心有千千鏢只能在戰鬥中使用。\n");
 
        if( (int)me->query_skill("tangmen-throwing", 1) < 180 )
                return notify_fail("你的唐門暗器手法不夠嫻熟，無法使用心有千千鏢。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不夠，無法使用心有千千鏢。\n");

        if( query_temp("xinqian", me) )
                return notify_fail("你忙于戰鬥，無法分神使用心有千千鏢了。\n");

        if( query("neili", me)<1500 )
                return notify_fail("你的內力不夠。\n");
        
        if( query("yanli", me)<100 )
                return notify_fail("你的眼力太差了，目標不精確！\n");       

        msg = HIR"\n$N突然身行一止，從懷中摸出一枚手掌大小的暗器，一揚手向$n擲去。\n只見$n的周身飛舞著無數的光影，卻聽不到一絲聲音。\n"NOR;
        message_vision(msg, me, target);
        addn("neili", -1500, me);
        set_temp("xinqian", 1, me);

        tell_object(target, HIR"\n你急忙屏氣凝神，希望能夠躲開這致命的一擊。\n"NOR);
        target->start_busy(6);

        remove_call_out("effect_biao");
        call_out("effect_biao", 8, me, target);

        return 1;
}

int effect_biao(object me, object target)
{
        int myskill, trskill;
        string msg;

        myskill = (int) (2 * (int)me->query_skill("dodge") + (query("combat_exp",me) / 1000) + (int)me->query_skill("tangmen-biaofa", 1)); 
        trskill = (int) (2 * (int)target->query_skill("dodge") + (query("combat_exp",target) / 1000)); 

        if ( ( myskill >= trskill ) && ( random(100) != 0 ) )
                {
                        msg = HIR"忽然那無數的光影一閃而沒，$n身行一頓，噴出一口鮮血，仰天而倒。\n"NOR;
                        message_vision(msg, me, target);
                        tell_object(target, HIR"你只覺得胸口一陣鑽心的疼痛。低頭一看只見那枚暗器已經深深的嵌在你的心口。\n血跡中隱約有幾個小字[心有千千...]。"NOR);
                        delete_temp("xinqian", me);
                        me->start_busy(5);
                        this_object()->move(target);
                        target->unconcious();
                }
        else
                {
                        tell_object(target, HIR"忽然那無數的光影一閃而沒，你心中一驚急忙運內力于全身。\n"NOR);
                        msg = HIR"$n雙臂急舞，衣袖帶起破風之聲。只聽當的一聲輕響，竟將那枚暗器磕飛開去。\n"NOR;
                        message_vision(msg, me, target);
                        if( query("neili", target)<800 )
                                set("neili", 0, target);
                        else
                                addn("neili", -1000, target);
                        delete_temp("xinqian", me);
                        me->start_busy(3);
                        destruct(this_object());
                }
        return 1;
}
