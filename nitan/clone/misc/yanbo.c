// yanbo.c 研砵

inherit ITEM;

void create()
{
        set_name("研砵", ({ "yanbo", "bo" }));
        set_weight(600);
        set_max_encumbrance(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "一只沉甸甸的瓷碗，可以用來磨藥。\n");
                set("value", 200);
        }
}

int is_container() { return 1; }

int can_make_medicine() { return 1; }