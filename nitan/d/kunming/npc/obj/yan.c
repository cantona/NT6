inherit ITEM;

void create()
{
        set_name("水煙", ({"shui yan", "shui", "yan"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一卷水煙絲。\n");
                set("unit", "卷");
                set("value", 10);
            }
}