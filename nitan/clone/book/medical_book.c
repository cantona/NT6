// advance_unarmed.c

inherit BOOK;

void create()
{
        set_name("本草綱目", ({ "bencao gangmu", "book" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
"封面上寫著「本草綱目」，是一個醫學的百科全書。\n");
                set("value", 2000);
                set("material", "paper");
                set("skill", ([
                        "name":         "medical",
                        "exp_required": 1000,
                        "jing_cost":    30,
                        "difficulty":   25,
                        "max_skill":    2100,
                ]));
        }
}
