#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIY "英雄勛章" NOR, ({ "hero medal", "hero", "xunzhang", "medal" }));
        set("long", HIR "殺倭寇活動第二名獎勵勛章，乃英雄的象征。\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/research_times", 500);
                set("armor_prop/practice_times", 500);
                //set("armor_prop/derive_times", 500);
        }
        set("auto_load", 1);
        setup();
}
