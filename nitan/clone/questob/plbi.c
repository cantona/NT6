// plbi.c

inherit ITEM;

void create()
{
        set_name("盤龍壁", ({ "panlong bi", "bi" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "一塊玉璧，上面印著一條龍，卻是天然形成，妙不可言。\n");
                set("value", 1);
                set("material", "jade");
        }
        setup();
}