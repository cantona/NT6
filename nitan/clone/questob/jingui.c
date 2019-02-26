// jingui.c

inherit ITEM;

void create()
{
        set_name("金龜", ({ "jin gui", "gui" }));
        set_weight(12000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "一隻碩大無比的純金製成的龜像，貴重無比。\n");
                set("value", 1);
                set("material", "gold");
        }
        setup();
}