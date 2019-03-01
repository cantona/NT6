#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "「無字天書」" NOR, ({ "wuzi tianshu", "wuzi", "tianshu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "傳說中蛋生獲仙人所贈的奇書，整本書不見一字。\n" NOR);
                set("value", 500000);
                set("unit", "本");
        }
}

void init()
{
        add_action("do_read", "read");
}

int do_read(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        if (me->is_fighting())
                return notify_fail("戰鬥中無法研讀。\n");

        if (arg && id(arg))
        {
                if( query("skybook/item/tianshu2", me )
                   || me->query_skill("literate") > 0)
                        return notify_fail(HIW "\n你輕輕翻開書頁，突然間一道強"
                                           "光射來，什麼都看不清楚。\n" NOR);

                log_file("static/using", sprintf("%s(%s) use 無字天書 at %s.\n",
                                                 me->name(1),query("id", me),
                                                 ctime(time())));

                message_vision(HIY "$N" HIY "輕輕翻開" + query("name") + HIY "書"
                               "頁，霎時間一道光華閃過$P" HIY "的面龐。\n" NOR, me);

                tell_object(me, HIC "冥冥中你似乎受到了某種的啟迪，往日的一切煩"
                                "惱漸漸消逝殆盡。\n" NOR);

                set("skybook/item/tianshu2", 1, me);
                me->start_busy(10);
                destruct(this_object());
                return 1;
        }
}

int query_autoload()
{
        return 1;
}