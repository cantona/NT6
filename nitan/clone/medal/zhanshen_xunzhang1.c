#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIY "戰神黃金勛章" NOR, ({ "zhanshen gold medal", "zhanshen", "xunzhang" }));
        set("long", HIY "華山論劍戰神組第一獲得的勛章，非常珍貴，乃強者的象征。\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/research_times", 250);
                set("armor_prop/practice_times", 250);
                set("armor_prop/derive_times", 250);
        }
        set("bindable", 2);
        set("auto_load", 1);
        setup();
}
