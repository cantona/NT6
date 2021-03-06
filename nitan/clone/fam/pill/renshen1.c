#include <ansi.h>
inherit __DIR__"pill";

void create()
{
        set_name(HIW "百年人蔘" NOR, ({ "bainian renshen", "bainian",
                                        "renshen", "shen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "產於高山上的珍貴藥材，服用後可提升內功等級。\n" NOR);
                set("base_unit", "株");
                set("base_value", 10000);
                set("base_weight", 300);
                set("only_do_effect", 1);
                set("pill_skill", "force");
                set("pill_point", 20000);
                set("force_point", 3);
                set("pill_msg1", HIR "你只覺一股暖氣散佈全身，説不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}