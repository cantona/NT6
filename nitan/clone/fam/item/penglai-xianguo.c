#include <ansi.h>

inherit ITEM;

int do_use(string arg);

void create()
{
        set_name(HIM "蓬萊仙果" NOR, ({"penglai xianguo", "penglai", "xianguo", "guo"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "\n這是一顆晶瑩紅透的仙果，據説服用後能功力大增。\n"
                                      "*服用(fuyong xianguo)需消耗吸靈壺，可獲得30萬經驗，25萬潛能，1000點貢獻及20萬體會（雙倍獎勵服務加倍）。\n"
                                      "*每服用一個蓬萊仙果會消耗一個吸靈壺，吸靈壺可從商城購買。\n" NOR);
                set("unit", "顆");
                set("value", 1);
        }
}

int query_autoload()
{
        return 1;
}


void init()
{
        add_action("do_use", "fuyong");       
}

int do_use(string arg)
{
        object me, ob;
        int exp, ys_exp, pot, tihui, gongxian;
                
        me = this_player();
        
        if(! objectp(present("penglai xianguo", me)))return 0;
        
        if(! objectp(ob = present("xiling hu", me)))
        {
                return notify_fail("你身上沒有吸靈壺，無法服用蓬萊仙果。\n");
        }
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
                 
        // 使用描述
        message_vision(HIY + "\n$N" HIY "一抬頭服下一顆蓬萊仙果，萬道金光閃過，功力大增 ……\n" NOR, me);

        exp = 300000;
        pot = 250000;
        tihui = 200000;
        gongxian = 1000;
        
        // 活動期間
        if( query("service/double_gift", me) )
        {
                exp *= 2;
                pot *= 2;
                tihui *= 2;
                gongxian *= 2;
        }
        
        tell_object(me, HIG "你服下蓬萊仙果後獲得了" + chinese_number(exp) + "經驗，" + chinese_number(pot) + "潛"
                            "能，" + chinese_number(gongxian) + "門派貢獻及" + chinese_number(tihui) + "體會。消耗吸靈壺一個。\n\n" NOR);

        // 消耗吸靈壺
        destruct(ob);
        
        // 元神增加經驗
        if( query("yuanshen/exp", me)<2000000000 )
        {
                ys_exp = exp / 5;
                exp -= ys_exp;
                addn("yuanshen/exp", ys_exp, me);
        }
        
        if( query("potential", me)>2000000000 || query("learned_points", me)>2000000000 )
        {
                set("potential",query("potential",  me)-query("learned_points", me), me);
                set("learned_points", 0, me);
        }
        if( query("experience", me)>2000000000 || query("learned_experience", me)>2000000000 )
        {
                set("experience",query("experience",  me)-query("learned_experience", me), me);
                set("learned_experience", 0, me);
        }
        if( query("combat_exp", me) <= 2000000000 )
        {
                addn("combat_exp", exp, me);
        }
        if( query("potential", me)<2000000000 )
        {
                addn("potential", pot, me);
        }
        if( query("experience", me)<2000000000 )
        {
                addn("experience", tihui, me);
        }
        
        addn("gongxian", gongxian, me);
        
        me->save();
        
        log_file("xianguo",query("id", me)+"at"+ctime(time())+"usepenglaixianguo.\n");
        
        destruct(this_object());
        
        return 1;
}