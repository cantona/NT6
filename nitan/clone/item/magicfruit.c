// xiandan.c 仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "魔界佛心果" NOR, ({ "magic fruit", "magic", "fruit" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆同時泛着奇異魔光和佛光的果實，據説吃了以後可以清除吃丹留下的後遺症。\n");
                set("value", 10000);
                set("unit", "顆");
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一顆" + this_object()->name() +
                       "。\n", me);

        if( query("gift/int/fail", me) )
        {
                addn("gift/int/fail", -1, me);
                if( query("gift/int/all", me) )
                {
                        addn("gift/int/all", -1, me);
                        if( query("gift/int/all", me)<1 )
                                delete("gift/int/all", me);
                }
                else
                        addn("gift/xiandan", -1, me);
                if( query("gift/int/fail", me)<1 )
                        delete("gift/int/fail", me);
        } else
        if( query("gift/str/fail", me) )
        {
                addn("gift/str/fail", -1, me);
                if( query("gift/str/all", me) )
                {
                        addn("gift/str/all", -1, me);
                        if( query("gift/str/all", me)<1 )
                                delete("gift/str/all", me);
                }
                else
                        addn("gift/shenliwan", -1, me);
                if( query("gift/str/fail", me)<1 )
                        delete("gift/str/fail", me);
        } else
        if( query("gift/con/fail", me) )
        {
                addn("gift/con/fail", -1, me);
                if( query("gift/con/all", me) )
                {
                        addn("gift/con/all", -1, me);
                        if( query("gift/con/all", me)<1 )
                                delete("gift/con/all", me);
                }
                else
                        addn("gift/xisuidan", -1, me);
                if( query("gift/con/fail", me)<1 )
                        delete("gift/con/fail", me);
        } else  
        if( query("gift/dex/fail", me) )
        {
                addn("gift/dex/fail", -1, me);
                if( query("gift/dex/all", me) )
                {
                        addn("gift/dex/all", -1, me);
                        if( query("gift/dex/all", me)<1 )
                                delete("gift/dex/all", me);
                }
                else
                        addn("gift/unknowdan", -1, me);
                if( query("gift/dex/fail", me)<1 )
                        delete("gift/dex/fail", me);
        } 
        
        tell_object(me, HIG "一股火熱驀然從全身升起，"
                            "你全身欲裂，恰在此時一股舒坦之意"
                            "油然而起，頓感全身舒服多了。\n" NOR);

        destruct(this_object());
        return 1;
}

