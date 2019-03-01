// pigpart.h

#include <ansi.h>

void setup()
{
        if (clonep()) set("only_do_effect", 1);
        ::setup();
}

int do_effect()
{
        return notify_fail("你想吃生" + name() + "？\n");
}

int broil(object me, object ob)
{
        object fob;

        me = this_player();
        if (me->is_busy())
        {
                write("你現在忙著呢，過會兒再烤吧。\n");
                return 1;
        }

        if (! query("food_remaining"))
        {
                write("這個好像沒有什麼必要再烤了吧？\n");
                return 1;
        }

        if (! query("only_do_effect"))
        {
                write("算了吧，東西不用烤兩遍，太老了。\n");
                return 1;
        }

        message_vision("$N把" + name() + "放在" + ob->name() +
                       "上細細的烤著，只聽畢啵畢啵的聲音，一"
                       "陣誘人的香味散了出來。\n", me);

        write(HIY "你把" + name() + HIY "烤好了！\n" NOR);
        set("long", "一" + query("unit") + "烤得香噴噴的野豬" + name() + "。\n");
        set_name("烤" + name(), 0);
        delete("only_do_effect");
        me->start_busy(1);
        return 1;
}