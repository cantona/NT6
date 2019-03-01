#include <ansi.h>
inherit __DIR__"pill";

void create()
{//3. 千年雪蓮        MAG        40000                20000        10                產于大雪山之上的珍貴藥材，服用後可提升輕功等級。

        set_name(MAG "千年雪蓮" NOR, ({ "qiannian xuelian",  "xuelian", "lian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", MAG "產于大雪山之上的珍貴藥材，服用後可提升輕功等級。\n" NOR);
                                                                set("unit", "株");
                set("value", 20000);
                set("weight", 300);
                set("pill_skill", "dodge");
                set("pill_point", 40000);
                set("force_point", 10);
                set("pill_msg1", HIW "你只感到清涼之意散布全身，說不出的舒服受用。\n" NOR);
                set("pill_msg2", HIC "你只覺靈台處清欣無比，精力得到了完全的補充。\n" NOR);
        }
        setup();
}