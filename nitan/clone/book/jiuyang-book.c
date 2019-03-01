// jiuyang.c

inherit BOOK;
inherit F_UNIQUE;
 
void create()
{
        set_name("「九陽真經」", ({ "jiuyang zhenjing", "jiuyang", "zhenjing" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
"這是一本薄薄的經書，只因油布包得緊密，雖長期藏在猿腹之中，書頁仍然完好無損。
書面上寫著幾個彎彎曲曲的文字，他一個也不識得，翻開來一看，四本書中盡是這些怪
文，但每一行之間，卻以蠅頭小楷寫滿了中國文字。\n",
        );
                set("value", 1);
                set("no_sell", 1);
                set("material", "paper");
                set("skill", ([
                        "name"        : "jiuyang-shengong",
				        "family_name" : "明教",
                        "exp_required":  100000,
                        "jing_cost"   :  120,
                        "difficulty"  :  40,
                        "max_skill"   :  380,
                        // "min_skill"   :  30,
                ]) );
        }
}

int query_autoload() { return 1; }
