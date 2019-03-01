#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIW "鑽石勛章" NOR, ({ "diamond medal", "diamond", "xunzhang", "medal" }));
        set("long", HIW "為泥潭做出重大貢獻而獲得的勛章，非常珍貴，乃睿者的象征。\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/research_times", 500);
                set("armor_prop/practice_times", 500);
                set("armor_prop/derive_times", 500);
        }
        set("bindable", 1); // 裝備綁定
        set("auto_load", 1);
        setup();
}
