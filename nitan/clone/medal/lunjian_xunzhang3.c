#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIC "論劍青銅勛章" NOR, ({ "lunjian bronze medal", "lunjian", "xunzhang" }));
        set("long", HIC "華山論劍天下第三獲得的勛章，非常珍貴，乃強者的象征。\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 100000);
                set("material", "bronze");
                set("armor_prop/research_times", 300);
                //set("armor_prop/practice_times", 300);
                //set("armor_prop/derive_times", 300);
        }
        set("bindable", 2);
        set("auto_load", 1);
        setup();
}
