// ironstone.c
inherit ITEM;
#include <ansi.h>
inherit F_UNIQUE;

void create()
{
        set_name(HIB"鐵石"NOR, ({ "iron stone","stone"}));
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long","這是一塊隕星鐵石，表面燒得焦黑的，看上去堅硬之極。\n似乎是製造兵器的絕好材料。\n");
                set("value", 0);
                set("material", "stone");
        }
}

void owner_is_killed()
{
        destruct(this_object());
}