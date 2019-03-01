#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "小回丹" NOR, ({"xiaohui dan", "xiaohui", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", HIR "一顆黑色的藥丸。恢復300點氣血和最大氣血。\n" NOR);
                set("value", 2000);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        if( time()-query_temp("last_eat", me)<2 )
        {
                write("你剛吃過藥，藥力還沒有完全吸收。\n");
                return 1;
        }
        set_temp("last_eat", time(), me);
        message_vision(HIR "$N" HIR "吃下一顆小回丹，只覺舒泰之極！\n" NOR, me);

        if( query("max_qi", me)-query("eff_qi", me) <= 300 )
        {
                 set("eff_qi",query("max_qi",  me), me);
                 if( query("max_qi", me)-query("qi", me) <= 300 )
                        set("qi",query("max_qi",  me), me);
                 
                 else 
                        addn("qi", 300, me);
        }


        else 
        {
                addn("eff_qi", 300, me);
                addn("qi", 300, me);
        }

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}