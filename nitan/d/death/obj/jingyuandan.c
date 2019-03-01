#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(RED "精元丹" NOR, ({ "jingyuan dan", "jingyuan", " dan"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "一顆神秘的神丹，散發出隱隱血光。\n" NOR);
                set("unit", "塊");
                set("value", 20000);
        }
}