// zysha.c

inherit ITEM;

void create()
{
        set_name("紫雲紗", ({ "ziyun sha", "sha", "silk" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "匹");
                set("long", "這是一匹淡紫色的華麗絲綢，薄得幾乎透明。\n");
                set("value", 5000);
                set("material", "silk");
        }
        setup();
}