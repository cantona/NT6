// /d/yixing/obj/tuchan.c
// Last Modified by winder on Jul. 12 2002

inherit ITEM;

void create()
{
        set_name("關東土產", ({ "tuchan" }));
        set("weight", 200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一包關東土產。\n");
                set("unit", "包");
                set("material", "wood");
                set("value", 300);
        }
        setup();
}