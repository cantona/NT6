// bowl.c

inherit ITEM;

void create()
{
        set_name("飯缽", ({ "bowl" }) );
        set_weight(5000);
        set_max_encumbrance(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一個和尚用的飯缽\n");
                set("value", 1);
        }
}

int is_container() { return 1; }