// zitie.c
// zqb

#include <ansi.h>

inherit ITEM;
void setup()
{}
void create()
{
        set_name( "字帖", ({ "zitie", "tie" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        RED
                        "\n“滿江紅”\n"
                        "\n"
                        "怒發沖冠，憑闌處，瀟瀟雨歇。\n"
                        "抬望眼，仰天長嘯，壯懷激烈。\n"
                        "三十功名塵與土，八千裡路雲和月。\n"
                        "莫等閒，白了少年頭，空悲切。\n"
                        "\n"
                        "靖康恥，尤未雪；臣子憾，何時滅。\n"
                        "駕長車踏破，賀蘭山缺。\n"
                        "壯志饑餐胡虜肉，笑談渴飲匈奴血。\n"
                        "待從頭，收拾舊山河，朝天闕。\n"
               NOR
                );
                set("value", 10000000);
                set("material", "paper");
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
        }
}