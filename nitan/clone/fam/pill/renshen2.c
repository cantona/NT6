#include <ansi.h>
inherit __DIR__"pill";

void create()
{
        set_name(NOR + YEL "千年人參" NOR, ({ "qiannian renshen", "qiannian",
                                              "renshen", "shen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "產于高山上的珍貴藥材，服用後可提升內功等級。\n" NOR);
                set("base_unit", "株");
                set("base_value", 15000);
                set("base_weight", 300);
                set("only_do_effect", 1);
                set("pill_skill", "force");
                set("pill_point", 35000);
                set("force_point", 5);
                set("pill_msg1", HIR "你只覺一股暖氣散布全身，說不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}