// tianxianggao.c 天香斷續膏

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_fu", "fu");
}

void create()
{
        set_name(HIY"天香斷續膏"NOR, ({"tianxiang duanxugao", "gao"}));
        set("unit", "塊");
        set("vegetable", 25);
        set("nostrum", 13);
        set("level", 50);
        set("long", "這是一塊天香斷續膏，是恆山派的療傷聖藥。受傷之後，適時敷(fu)藥，當有起死之功。\n");
        set("pour_type", "1");
        setup();
}

int do_fu(string arg)
{
        object me=this_player();

        if(!id(arg)) return notify_fail("你要敷什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要敷什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢敷，小心別敷歪了。\n");

        if( query("eff_jing", me) >= query("max_jing", me) && 
                query("eff_qi", me) >= query("max_qi", me) && 
                query("neili", me) >= query("max_neili", me) )
        {
                message_vision("$N沒必要敷天香斷續膏。\n",me);
        }
        else
        {
                set("eff_jing",query("max_jing",  me), me);
                set("jing",query("eff_jing",  me), me);
                set("eff_qi",query("max_qi",  me), me);
                set("qi",query("eff_qi",  me), me);
                addn("neili",query("max_neili",  me), me);
                message_vision("$N拿出一塊天香斷續膏，運內力捂熱後，“啪”地一聲，敷在創口上。\n",me);
                destruct(this_object());
        }
        return 1;
}