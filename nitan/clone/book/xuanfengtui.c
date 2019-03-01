//Cracked by Kafei
inherit BOOK;

void create()
{
        set_name("旋風掃葉腿心法", ({"xin fa", "book", "fa"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long",
"一張薄紙，上面密密麻麻寫滿了蠅頭小楷。\n");
                set("material", "paper");
                set("skill", ([
                        "name": "xuanfeng-tui", // name of the skill
                        "family_name" : "桃花島",
                        "exp_required": 0,      // minimum combat
                        "jing_cost": 10,        // jing cost every time
                        "difficulty":   20,     // the base int to learn
                        "max_skill":    30,    // the maximum level you
                ]) );
        }
}

