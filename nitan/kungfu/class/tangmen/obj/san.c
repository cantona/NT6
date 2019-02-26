// san.c
#include <ansi.h>
#include <weapon.h>
inherit ITEM;

void create()
{
        set_name(HIG"散花天女" NOR, ({"sanhua tianyu"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "這是一枚四川唐門祕製的暗器散花天女，威力無比。\n");
                set("unit", "枚");
                set("value", 21);         
        }
        setup();
}

