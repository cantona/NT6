// guai.c

inherit ITEM;

void create()
{
        set_name("怪石", ({ "guai shi", "guai", "shi" }) );
        set_weight(500);
        set_max_encumbrance(80000);
        set("no_get", 1);
        set("no_shown", 1);
        set("prep","under");
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "參差不齊的怪石。\n");
                set("value", 1);
        }
}
int is_container() { return 1; }