// cookery_book.c

inherit ITEM;

void create()
{
        set_name( "烹飪入門", ({ "shu", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是本有些年代的書了，封皮上寫著《烹飪入門》。\n");
                set("value", 100);
                set("material", "paper");
                set("skill", ([
                        "name": "cookery",
                        "exp_required": 10000,
                        "jing_cost": 40,
                        "difficulty": 20,
                        "max_skill": 150,
                        "min_skill": 67,
                ]) );
        }
}
