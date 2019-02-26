// tiegy.c

inherit ITEM;

void create()
{
        set_name("鐵觀音", ({ "tie guanyin", "guanyin" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "這是一做鐵製觀音雕像，黑黝黝的，並不美麗。\n");
                set("value", 1000);
                set("material", "iron");
        }
        setup();
}