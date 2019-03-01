// yupei.c
inherit ITEM;

void create()
{
        set_name("玉佩", ({"yu pei", "yu","pei"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long",
"這是一塊精美的藍田玉，入手溫潤無比。\n");
        set("value", 80000);
                set("material", "stone");
        }
}
