// xisuidan.c 仙丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "洗髓丹" NOR, ({ "xisui dan", "dan", "xisuidan" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆黑不溜秋的丹藥，據説吃了可以增強根骨。增加先天屬性至五點\n");
                set("value", 10000);
                set("unit", "顆");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一顆" + this_object()->name() +
                       "。\n", me);
        if( query("gift/xisuidan", me) >= 5 || 
            query("gift/con/succeed", me) >= 5 )
        {
                message_vision("$N突然放了一個奇臭無比的響屁。\n", me);
                tell_object(me, "你覺得大概是吃壞了肚子。\n");
        } else
        if (random(5) == 0)
        {
                addn("gift/con/fail", 1, me);
                tell_object(me, "不過你覺得好像沒什麼作用。\n");
        } else
        {
                message("vision", "你似乎聽見" + me->name() + "的骨頭嘩啦啦的響。\n",
                                  environment(me), ({ me }));
                tell_object(me, HIY "你渾身的骨骼登時嘩啦啦的響個不停，可把你嚇壞了，"
                                "好在一會兒就停了下來，似乎筋骨更靈活了。\n" NOR);
                addn("gift/con/succeed", 1, me);
                addn("con", 1, me);
        }

        if( query("gift/xisuidan", me)<5 )
                addn("gift/xisuidan", 1, me);
        destruct(this_object());
        return 1;
}
