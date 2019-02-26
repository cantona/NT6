// expert_staff.c

inherit BOOK;

void create()
{
        set_name("棍法祕要", ({ "club book", "book" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
"封面上寫著「棍法祕要）」\n");
                set("value", 50000);
                set("material", "paper");
                set("skill", ([
                        "name":         "club",
                        "exp_required": 1000,
                        "jing_cost":    50,
                        "difficulty":   30,
                        "max_skill":    99,
                        "min_skill":    20,
                ]));
        }
}
