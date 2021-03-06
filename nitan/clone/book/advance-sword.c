// advance_sword.c

inherit BOOK;

void create()
{
        set_name("劍法詳解", ({ "sword book", "book" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
"封面上寫著「劍法詳解）」\n");
                set("value", 10000);
                set("material", "paper");
                set("skill", ([
                        "name":         "sword",
                        "exp_required": 1000,
                        "jing_cost":    30,
                        "difficulty":   25,
                        "max_skill":    49,
                        "min_skill":    20,
                ]));
        }
}
