// This program is a part of NT MudLIB

inherit ITEM;

void create()
{
        set_weight(80000);
        set_name("火藥", ({"huo yao", "powder"}));
        set("long", "這是一桶火藥。\n");
        set("unit", "桶");
        set("value",100);
        set("load",15);
        setup();
}
