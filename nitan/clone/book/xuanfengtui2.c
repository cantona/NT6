//Cracked by Kafei

inherit BOOK;

void create()
{
        set_name( "旋風掃葉腿心法", ({ "xin fa","book", "fa" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "
一張薄紙，上面密密麻麻寫滿了蠅頭小楷，旁邊似乎有些批注。\n");
                set("value", 200);
                set("material", "paper");
                set("skill", ([
                        "name": "kick", // name of the skill
                        "exp_required": 0,      // minimum combat experience required
                        "jing_cost": 10,        // jing cost every time study this
                        "difficulty":   20,     // the base int to learn this skill
                        "max_skill":    100,    // the maximum level you can learn
                ]) );
        }
}
