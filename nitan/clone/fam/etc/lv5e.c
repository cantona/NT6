inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "通天草" NOR, ({"tongtian cao", "tongtian", "cao"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "一株生長於極高山崖上的通體瑩綠的小草。\n" NOR);
                set("unit", "株");
                set("value", 15000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
