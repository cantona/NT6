// zijinchui.c

inherit ITEM;

void create()
{
        set_name("紫金錘", ({ "zijin chui", "chui" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "對");
                set("long", "這是一對八稜紫金錘，精美的裝飾品。\n");
                set("value", 4000);
                set("material", "copper");
        }
        setup();
}