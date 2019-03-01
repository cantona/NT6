// zisj.c

inherit ITEM;

void create()
{
        set_name("紫水晶", ({ "zi shuijing", "zi" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "看上去和水晶相類，實際上卻不是，故此珍貴無比。\n");
                set("value", 1);
                set("material", "stone");
        }
        setup();
}