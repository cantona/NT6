// qingdan.c
// more work needed to use this object to make poison

inherit ITEM;

void create()
{
        set_name("青蛇膽", ({ "qing dan", "qing" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "這是一隻綠瑩瑩的青蛇膽，是製備『蛇膽膏』"
                            "的原料。\n");
                set("value", 100);
                set("only_do_effect", 1);
        }
        setup();
} 

int do_effect(object me)
{
        return notify_fail("你找死啊。\n");
}
