// receipt.c 回執

inherit ITEM;

int is_receipt() { return 1; }

void create()
{
        set_name("回執", ({ "receipt" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "這是一張回執！\n");
                set("value", 1);
                set("no_sell", 1);
        }
        setup();
}