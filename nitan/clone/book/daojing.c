// daojing.c

inherit ITEM;

void create()
{
        set_name("萬壽道藏", ({ "wanshou book", "book" }));
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一部萬壽道藏。徽宗皇帝於政和年間，遍搜普天下道家之書，雕版印行，一共有五千四百八十一卷，委派刻書之人，便是黃裳……。\n");
                set("value", 5000);
                set("material", "paper");
                set("skill", ([
                        "name"        : "taoism",
                        "exp_required":        200000,
                        "jing_cost"   : 50,
                        "difficulty"  : 30,
                        "min_skill"   : 99,
                        "max_skill"   : 149,
                ]) );
        }
}