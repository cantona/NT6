// hand_book.c

inherit ITEM;

void create()
{
        set_name("棋譜", ({ "qi pu", "pu" }));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本薄薄的小冊，上面密密麻麻的寫滿了蠅頭小楷，橫豎棋格。\n");
                set("value", 500);
                set("material", "silk");
                set("skill", ([
                        "name":    "chess",      // name of the skill
                        "exp_required": 0,      // minimum combat experience required
                        "jing_cost":    20,     // jing cost every time study this
                        "difficulty":   20,     // the base int to learn this skill
                        "max_skill":    400     // the maximum level you can learn
                ]) );
        }
}
