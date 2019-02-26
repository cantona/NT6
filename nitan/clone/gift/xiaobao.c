// xiaobao.c 小寶

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "小寶" NOR, ({ "xiao bao", "bao", "xiaobao" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆金燦燦的丹藥，據説可以養血美顏。\n");
                set("value", 20000);
                set("unit", "顆");
                set("per",5);
                set("time",864000);
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        if( query("have_meirong_dan", me) )
        {
                tell_object(me, "你已經服用過類似的藥品，藥力尚未消失，不適宜繼續服用！\n");
                return 1;
        }
        
        log_file("static/using", sprintf("%s(%s) eat 小寶 at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        message_vision("$N一仰脖，吞下了一顆" + this_object()->name() +
                       "。\n", me);

        message("vision", "你似乎感覺" + me->name() + "的面容漸漸模糊起來，不由嚇了一大跳！\n",
                          environment(me), ({ me }));

        tell_object(me, HIY "你周身的皮膚癢癢的似乎要崩裂開來，"
                        "好在一會兒就停了下來，渾身上下輕鬆很多。\n" NOR);

        set("have_meirong_dan",query("per",  this_object()), me);
        set("meirong_time", time()+query("time", this_object()), me);
        addn_temp("apply/per",query("per",  this_object()), me);
        set_temp("meirong_dan_used", 1, me);
        
        destruct(this_object());
        return 1;
}
int query_autoload() { return 1; } 
