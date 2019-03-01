// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        int i;
        if( !query("bunch/bunch_name", me) )
                return notify_fail("你沒有參加任何幫會，無法通過切蹉武功征招NPC。\n");
                
        if (! arg)
                return notify_fail("你要和誰切磋武功？\n");
                
        if (! ob = present(arg, environment(me)))
                return notify_fail("這兒沒有這麼個人。\n");
                
        if (! ob->is_character())
                return notify_fail("看清楚！那並不是個生物。\n");
                
        if (playerp(ob))
                return notify_fail("你只能與NPC切蹉武功。\n");
                
        if (! living(ob)) return notify_fail("你得先把他弄醒再說。\n");
        
        if (me->is_fighting() || me->is_busy())
                return notify_fail("你正忙著呢。\n");
                
        if( query("bunch/zhengzhao", ob) != 1 )
                return notify_fail("這個NPC不能用切磋武功的方式征招。\n");
                
        if( query("bunch/bunch_name", ob) == query("bunch/bunch_name", me) )
                return notify_fail("這個NPC已經是本幫兄弟，不必通過切蹉武功來征招。\n");
                
        if ((object)query_temp("invite/target", ob) != me)
                return notify_fail("你必須要先邀請(yaoqing)這個NPC。\n");
                
        if (ob->is_fighting() || ob->is_busy())
                return notify_fail("對方正忙著呢。\n");
                
        if( query("bunch/bunch_name", ob) && query("bunch/zhongcheng", ob)>query("meili", me) )
                return notify_fail("看樣子對方不想和你切蹉武藝。\n");
                
        if( query("qi", ob)*100<query("max_qi", ob)*80 )
                return notify_fail("看樣子對方不想和你切蹉武藝。\n");
                
        message_vision(HIY"$N道：“如此" + RANK_D->query_self(ob) +
                       "我便領教"+query("name", me)+"的高招！”\n"NOR,
                       ob, me);
                       
        if( query_temp("invite/target", ob) )
                delete_temp("invite/target", ob);
                
        me->fight_ob(ob);
        ob->fight_ob(me);
        remove_call_out("check_qi");
        call_out("check_qi", 1, me, ob);
        return 1;
}

void check_qi(object me,object ob)
{
        
        if (! objectp(me) || ! objectp(ob)) return;
        
        if( !query("bunch/bunch_name", me))return ;
        
        if (me->is_fighting(ob))
        {
                call_out("check_qi", 1, me, ob);
                return;
        }
        
        if (! environment(ob))   return;
        
        if (environment(me) != environment(ob))    return;
        
        if( query("qi", ob)>query("max_qi", ob)/2 )
        {
                message_vision("$N哈哈一笑，沖著$n道：“看來" + RANK_D->query_respect(me)
                               + "還得苦練才行啊。”\n", ob, me);                
        }
        
        else if (ob->query_last_damage_from() != me) 
        {
                message_vision("$N哼了一聲道：“靠他人幫忙算什麼意思？”\n",ob);
        }
        else            
        {
                message_vision("$N對$n一抱拳道：“" + RANK_D->query_respect(me)
                               + "果然厲害，" + RANK_D->query_self(ob)
                               + "佩服得緊啊。”\n", ob, me);
                ob->do_join_bunch(me);
        }
}

