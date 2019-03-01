// blade_book1.c

inherit ITEM;

void create()
{
        set_name("「刀術」", ({ "blade book", "book", "shu" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本普普通通的介紹刀法的書，字跡很是潦草。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name":         "blade",
                        "exp_required": 100 ,
                        "jing_cost":    20+random(20),
                        "difficulty":        20,
                        "min_skill":        20,
                        "max_skill":        30
                ]) );
        }
}