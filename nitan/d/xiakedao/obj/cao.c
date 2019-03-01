// cao.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("腐心草", ({"fuxin cao", "cao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一朵無根小草，長得很小，卻給人一種欣欣向榮的感覺。\n");
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        message_vision(HIG "$N" HIG "吃下一株腐心草，頓"
                       "然間有點肚子疼...趕緊去廁所！\n" NOR, this_player());
        destruct(this_object());
        return 1;
}