// xiaoshu.c 消暑丸

inherit ITEM;

#include <ansi.h>

void create()
{
        set_name(HIY"消暑丸"NOR, ({"xiaoshu wan", "xiaoshuwan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包治療中暑的藥，立刻見效。\n");
                set("value", 600);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if (!me->query_condition("ill_zhongshu"))
        {
                write("你現在又沒有中暑，別亂吃藥。\n");
                return 1;
        } else {
                me->clear_condition("ill_zhongshu");
                message_vision("$N吃下一包消暑丸，看起來精神多了。\n", me);
                me->start_busy(2);
                destruct(this_object());
                return 1;
        }
}