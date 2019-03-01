// chutou.c
inherit ITEM;

void create()
{
        set_name("鋤頭", ({ "chu tou" }));
        set_weight(12000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一把鋤地的鋤頭。\n");
                set("unit", "把");
                set("value", 0);
        }
}
