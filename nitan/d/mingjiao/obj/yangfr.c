// yangfr.c

inherit ITEM;
void create()
{
        set_name("陽夫人遺骨", ({ "corpse" }) );
        set_weight(30000);
        set_max_encumbrance(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "具" );
                set("long", "這是一具明教前任教主陽頂夫人的遺骨。她胸口插着一口精亮的匕首。\n");
                set("no_get", "人都死了，何必還煩動她的屍骨？\n");
        }
        setup();
}
