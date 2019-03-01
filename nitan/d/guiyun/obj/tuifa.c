// Obj: /d/guiyun/obj/tuifa.c 旋風掃葉腿法
// Last Modified by winder on Jul. 9 2001

inherit ITEM;

void create()
{
        set_name("旋風掃葉腿圖解", ({ "tuifa tujie", "tujie", "shu", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("treasure", 1);
                set("unit", "本");
                set("long", "這本腿法中詳細地畫著黃藥師所創的旋風掃葉腿的圖解，雖然對你來說略顯艱深，但用它來領悟基本腿法的訣竅卻是可以的。\n");
                set("value", 40);
                set("material", "paper");
                set("skill", ([
                        "name":        "leg",                // name of the skill
                        "exp_required":        100,        // minimum combat experience required
                        "jing_cost":        15,        // jing cost every time study this
                        "difficulty":        25,        // the base int to learn this skill
                        "max_skill":        30        // the maximum level you can learn
                ]) );
        }
}