// Last Modified by winder on Nov. 17 2000
// zitie.c

#include <ansi.h>
inherit ITEM;
void setup()
{}
void create()
{
        set_name( HIB"字帖"NOR, ({ "zitie", "tie" }));
        set_weight(200);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        RED
                        "\n“滿江紅”\n"
                        "\n"
                        "怒髮衝冠，憑闌處，瀟瀟雨歇。\n"
                        "抬望眼，仰天長嘯，壯懷激烈。\n"
                        "三十功名塵與土，八千里路雲和月。\n"
                        "莫等閒，白了少年頭，空悲切。\n"
                        "\n"
                        "靖康恥，尤未雪；臣子憾，何時滅。\n"
                        "駕長車踏破，賀蘭山缺。\n"
                        "壯志飢餐胡虜肉，笑談渴飲匈奴血。\n"
                        "待從頭，收拾舊山河，朝天闕。\n" NOR
                );
                set("value", 0);
                set("material", "paper");
        }
}