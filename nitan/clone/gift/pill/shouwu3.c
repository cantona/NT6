#include <ansi.h>
inherit __DIR__"pill";

void create()
{//3. 千年何首烏        HIW        40000                20000        10                產于極北森林之上的珍貴藥材，服用後可提升招架等級。

        set_name(HIW "千年何首烏" NOR, ({ "qiannian heshouwu", "heshouwu",  "shouwu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", HIW "產于極北森林之中的珍貴藥材，服用後可提升招架等級。\n" NOR);
                                                                set("unit", "支");
                set("value", 20000);
                set("weight", 300);
                set("pill_skill", "parry");
                set("pill_point", 40000);
                set("force_point", 10);
                set("pill_msg1", HIR "你只覺一股暖氣散布全身，說不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}