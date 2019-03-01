// sleepbag.c
inherit ITEM;

void create()
{
        set_name("睡袋",({"sleepbag"}));
        set_weight(7000);
        set_max_encumbrance(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
            set("long",
                "一個睡袋，江湖人士用來在野外睡覺用的。\n");
            set("unit","個");
            set("value", 1000);
        }
}
