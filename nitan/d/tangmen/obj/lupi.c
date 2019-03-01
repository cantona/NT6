// lupi.c 野鹿皮

inherit ITEM;

void create()
{
        set_name("野鹿皮", ({"lu pi", "pi"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一張完整的野鹿皮，摸上去柔軟光滑。\n");
                set("unit", "張");
                set("value", 200);
        }
}