// needfire.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "篝火" NOR, ({ "needfire", "gou huo", "huo" }) );
        set_weight(100);
        if (clonep())
        {
                set_default_object(__FILE__);
                call_out("light", 30 + random(20));
        } else
        {
                set("unit", "堆");
                set("long", "這是一堆正在燃燒的篝火，看上去可以在上面烤烤東西(kao)。\n");
                set("no_get", "你也不怕燒了手？\n");
                set("no_fire", "這正在燃燒啊，你的腦子是不是有問題？\n");
        }
        setup();
}

void init()
{
        add_action("do_kao", "kao");
}

void set_light_time(int n)
{
        remove_call_out("light");
        call_out("light", n + random(n / 2));
}

void light()
{
        call_out("destroy", 10 + random(10));
        if (environment())
                message("vision", HIR "篝火漸漸的黯淡了下去，似"
                        "乎快要熄滅了。\n" NOR, environment());
        set("long", "這是一堆正在燃燒的篝火，火光暗淡，看上去快要熄滅了。\n");
}

void destroy()
{
        if (environment())
                message("visoin", RED "火燄最後掙紮著跳動了幾下，"
                        "漸漸的熄滅了，只留下了一點灰燼。\n" NOR,
                        environment());
        destruct(this_object());
}

int do_kao(string arg)
{
        object ob;
        object me;

        if (! arg)
                return notify_fail("烤點什麼東西呢？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上好像沒有這樣東西。\n");

        return ob->broil(me, this_object());
}

int move(mixed dest, int raw)
{
        int res;

        if (objectp(dest) && dest->is_character())
                return 0;

        if (environment())
                addn_temp("warm", -20, environment());

        res = ::move(dest, raw);

        if (environment())
                addn_temp("warm", 20, environment());

        return res;
}

void remove(string euid)
{
        ::remove(euid);
        if (environment())
                addn_temp("warm", -20, environment());
}