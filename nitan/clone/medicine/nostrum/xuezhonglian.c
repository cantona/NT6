// Last Modified by winder on Sep. 12 2001
// xuezhonglian.c 雪中蓮

inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "雪中蓮" NOR, ({"xuezhong lian", "lian"}));
        set("unit", "朵");
        set("long","這是一朵生長在雪山上的雪蓮，它潔白的花瓣上附著幾顆晶瑩的露珠，正散發著淡淡的幽香。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        int force_limit, neili_limit;
        object me = this_player();

        force_limit = me->query_skill("force")*10;
        neili_limit=query("max_neili", me);

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        if( neili_limit>force_limit)addn("max_neili", -10, me);
        addn("max_neili", random(10), me);
        message_vision( HIG"$N吃下一朵"NOR, me);
        message_vision( HIW"雪中蓮"NOR, me);
        message_vision( HIG"，頓時覺得靈台一清，一股熱氣直穿任督二脈，頭上冒出絲絲熱氣。\n"NOR, me);
        destruct(this_object());
        return 1;
}
void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
        remove_call_out("destlian");
        call_out("destlian", 10);
}
void destlian()
{
        message_vision("$N慢慢幹枯萎縮，一會就溶化消失掉了。\n", this_object());
        destruct(this_object());
}
