//Cracked by Kafei
// ni.c 泥

inherit ITEM;

void create()
{
        set_name("濕泥", ({"shi ni", "mud"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一團從西湖挖來的濕泥。\n");
                set("unit", "團");
                set("value", 0);
        }

        setup();
}
