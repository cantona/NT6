#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIW "崑崙鏡" NOR, ({ "kunlun jing", "kunlun", "jing" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "面");
                set("long", HIW "這是一面通體銀光的鏡子，據説擁有破開太虛的能力。\n" NOR);
        }

        setup();
}

