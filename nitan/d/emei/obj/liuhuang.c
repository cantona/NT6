// liuhuang.c 硫磺
inherit ITEM;
void create()
{
        set_name("硫磺", ({"liuhuang"}));
        set_weight(40);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊黃色的硫磺晶體。\n");
                set("unit", "塊");
                set("value", 10);
        }
}