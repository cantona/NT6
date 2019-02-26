// qiankun-xinfa 乾坤大挪移心法

#include <ansi.h>

inherit BOOK;

void setup()
{
}

void create()
{
        set_name("羊皮", ({ "qiankunbook", "skin" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", @LONG
這是一張羊皮，一面有毛，一面光滑。第一行是“明教聖
火心法，乾坤大挪移”十一個字。原來這就是武林第一祕
籍《乾坤大挪移》心法，相傳來自西域山中老人所作。
LONG );
                set("material", "paper");
                set("skill", ([
                        "name"         : "qiankun-danuoyi",
                        "family_name"  : "明教",
                        "exp_required" : 1000000,
                        "jing_cost"    : 200,
                        "difficulty"   : 45,
                        "max_skill"    : 380,
                        "need" : ([ "sanscrit" : 200 ]),
                ]) );
        }
}
