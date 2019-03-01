// xiaopu.c

inherit BOOK;

void create()
{
        set_name("簫譜", ({ "xiao pu", "pu" }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本薄薄的簫譜，記載了一些吹簫的方法。\n");
                set("value", 10);
                set("material", "paper");
                set("skill", ([
                        "name":         "chuixiao-jifa",
                        "jing_cost":        20,
                        "difficulty":        20,
                        "max_skill":        150,
                        "min_skill":    10,
                ]) );
        }
}
