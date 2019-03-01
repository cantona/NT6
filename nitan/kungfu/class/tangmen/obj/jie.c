#include <ansi.h>
#include <weapon.h>
inherit ITEM;

void create()
{
        set_name(HIG "心有千千結" NOR, ({"qianqian jie"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "這是一枚四川唐門秘制的暗器心有千千結，一條飛索，有無數個結，威力無比。\n");
                set("unit", "條");
                set("value", 21);
        }
        setup();
}