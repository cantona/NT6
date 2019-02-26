#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIW "戰神白銀勛章" NOR, ({ "zhanshen silver medal", "zhanshen", "xunzhang" }));
        set("long", HIW "華山論劍戰神組第二獲得的勛章，非常珍貴，乃強者的象徵。\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 150000);
                set("material", "silver");
                set("armor_prop/research_times", 250);
                set("armor_prop/practice_times", 250);
                //set("armor_prop/derive_times", 250);
        }
        set("bindable", 2);
        set("auto_load", 1);
        setup();
}
