// lugu.c 野鹿骨

inherit ITEM;

void create()
{
        set_name("鹿骨", ({"lu gu", "gu", "bone"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一根剛剛剔出來的野鹿骨頭。\n");
                set("unit", "根");
                set("value", 300);
        }
}