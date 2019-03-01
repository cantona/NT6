inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + WHT "何首烏" NOR, ({ "he shouwu", "he", "shouwu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一支已成人形的何首"
                            "烏，看來可以入藥。\n" NOR);
                set_weight(800);
                set("value", 10000);
                set("unit", "支");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if( query("max_jingli", me)<100 )
        {
                write(HIW "你吃下了一支何首烏，只覺得精神健旺之極。\n" NOR);
                me->improve_jingli(2 + random(1));
        } else
        {
                write(HIC "你吃下了一支何首烏，但是好象沒什麼用。\n" NOR);
        }
        destruct(this_object());
        me->unconcious();
        return 1;
}