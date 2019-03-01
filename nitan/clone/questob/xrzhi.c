// xrzhi.c

inherit ITEM;

void create()
{
        set_name("仙人指", ({ "xianren zhi", "zhi" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "看上去如同真人手指一般，可卻是未經人加工琢磨的天然玉石。\n");
                set("value", 1);
                set("material", "jade");
        }
        setup();
}