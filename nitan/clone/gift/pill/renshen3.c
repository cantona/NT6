#include <ansi.h>
inherit __DIR__"pill";

void create()
{//3.  千年人參        HIY        40000                20000        10                產于高山上的珍貴藥材，服用後可提升基本內功等級。

        set_name(HIY "千年人參" NOR, ({ "qiannian renshen",  "renshen", "shen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", HIY "產于高山上的珍貴藥材，服用後可提升基本內功等級。\n" NOR);
                                                                set("unit", "株");
                set("value", 20000);
                set("weight", 300);
                set("pill_skill", "force");
                set("pill_point", 40000);
                set("force_point", 10);
                set("pill_msg1", HIR "你只覺一股暖氣散布全身，說不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}