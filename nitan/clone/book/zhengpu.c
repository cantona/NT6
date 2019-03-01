// zhengpu.c

inherit BOOK;

void create()
{
        set_name("箏譜", ({ "qin pu", "pu" }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本薄薄的箏譜，記載了一些演奏古箏的方法。\n");
                set("value", 10);
                set("material", "paper");
                set("skill", ([
                        "name":         "guzheng-jifa",
                        "jing_cost":        20,
                        "difficulty":        20,
                        "max_skill":    200,
                        // "min_skill":    10,
                ]) );
        }
}
