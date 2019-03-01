// tongxq.c

inherit ITEM;

void create()
{
        set_name("銅喜鵲", ({ "tong xique", "xique" }));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "這是一黃銅喜鵲飾物，象征著吉祥如意。\n");
                set("value", 5000);
                set("material", "copper");
        }
        setup();
}