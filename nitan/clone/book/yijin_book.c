// yijinjing.c

inherit BOOK;
#include <ansi.h>

void create()
{
        set_name(YEL"易筋經"NOR, ({ "yijinjing" }));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "卷");
                set("long",
                "易筋經\n"
                "這是一卷古樸絲織經軸，看來很有年月了，上面文字堅深，不知你識
也不識。易筋經是少林鎮寺之寶 ，一直妥藏此處。\n");
                set("value", 10);
                set("material", "silk");
                set("skill", ([
                        "name":         "yijinjing",    // name of the skill
                        "exp_required": 100000, // minimum combat experience required
                        "jing_cost":    50,     // jing cost every time study this
                        "difficulty":   30,     // the base int to learn this skill
                        "max_skill":    380     // the maximum level you can learn
                ]) );
        }
}

