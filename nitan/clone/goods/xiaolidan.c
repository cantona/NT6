#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "消戾丹" NOR, ({ "xiaoli dan", "xiaoli", "dan" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "一顆紫色的精致奇丹，具有著神話般的功效，傳說\n"
                                "吃了後可以消除人物的戾氣。\n" NOR);
                set("value", 500000);
                set("unit", "粒");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$N一仰脖，吞下了一粒" + this_object()->name() +
                       "。\n", me);
                       
        set("total_hatred", 0, me);
        
        write(HIM "你只覺得靈台一片空明，純凈無比，你的戾氣消除了。\n" NOR);
        destruct(this_object());
        return 1;
}
