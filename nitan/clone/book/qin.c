// qin.c

inherit BOOK;

void create()
{
        set_name("琴譜", ({ "qin pu", "pu" }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本薄薄的琴譜，記載了一些彈琴的方法。\n");
                set("value", 10);
                set("material", "paper");
                set("skill", ([
                        "name":         "tanqin-jifa",
                        "jing_cost":        20,
                        "difficulty":        20,
                        "max_skill":        150,
                        "min_skill":    10,
                ]) );
        }
}
