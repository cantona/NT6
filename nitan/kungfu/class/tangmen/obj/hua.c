// tanghua.c
#include <ansi.h>
#include <weapon.h>
inherit ITEM;

void create()
{
        set_name(HIG "唐花" NOR, ({"tang hua", "hua" }));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIR"這是一朵鐵花，但美若曇花，精緻玲瓏，讓人一看之下，就動人心魄。\n"NOR);
                set("unit", "枚");
                set("value", 21);
        }
        setup();
}
