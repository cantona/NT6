// This program is a part of NT MudLIB
// rideto.c

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        object riding, env;
        string where;

        if( !arg )
        {
                MAP_D->show_trans(me);
                return 1;
        }
                
        if (me->over_encumbranced())
                return notify_fail("你的負荷過重，動彈不得。\n");

        if (me->query_encumbrance() < 0)
                return notify_fail("你的負荷出現故障，動彈不得。\n");

        if( query_temp("sleeped", me) )
                return notify_fail("你現在正躺著呢。\n");

        if (me->is_in_prison())
                return notify_fail("你正在做牢呢，你想幹什麼？！\n");

        if (me->is_fighting())
                return notify_fail("你現在正在戰鬥！\n");

        if( me->is_ghost() )
                return notify_fail("你還是等還陽後再說吧。\n");

        if( me->is_busy() || query("doing", me) )
                return notify_fail("你的動作還沒有完成，不能移動。\n");

        if( !objectp(riding=query_temp("is_riding", me)) )
                return notify_fail("你還沒有坐騎！\n");

        if( !present(query("id", riding),me) )
                return notify_fail("你的坐騎不在你身邊！\n");

/*
        if( !query("outdoors", environment(me)) )
                return notify_fail("在房間裡不能亂跑！\n");
*/
        // 帳篷中不能rideto
        env = environment(me);
        if( objectp(env) )
        {
                if( base_name(env) == "/clone/fam/item/zhangpeng" || 
                        base_name(env) == "/clone/fam/item/zhangpeng2" )
                {
                        return notify_fail("此處不能騎馬！\n");
                }
        }

        if( query("no_rideto", env) )
                return notify_fail("這裡無法騎馬穿梭。\n");
               
        if( query("no_magic", env) || query("maze", env) )
                return notify_fail("你發現這裡有點古怪，你的坐騎好象不聽你的指揮！\n");

        //if (me->query_condition("killer"))
        //        return notify_fail("你有命案在身呢，你還是小心為妙，不宜在官道上肆無忌憚行走！\n");

        if( objectp(riding=query_temp("is_riding", me)) )
        {           
                MAP_D->move_to(me, arg);
                return 1;
        }
        
        return notify_fail("你還是先找匹坐騎再說吧。\n");
}

int help(object me)
{
        write(@HELP
指令格式 : rideto <地點>

這個指令可以讓你騎馬到指定地點，如果指定不帶參數可以
參看你所能到的地方。

HELP );
        return 1;
}
