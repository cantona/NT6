// key2.c

inherit ITEM;

void create()
{
        set_name("鐵鑰匙", ({"tie key", "key", "yaoshi"}));

        set("long", "這是一把鐵鑰匙，不知道有什麼用。\n");
        set("unit", "把");
        set("weight", 10);
        set("no_drop", 1);
}
