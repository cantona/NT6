inherit ITEM;
#include <ansi.h>

void create()
{
      set_name(HIW "輪回﹒裁決" NOR, ({"lunhui caijue","lunhui","caijue" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
              set("long", HIM "輪回之苦﹒三界裁決。\n" NOR);
                set("unit", "塊");
                set("value", 5000);
           set("enchase/name", "輪回﹒裁決");
               set("enchase/point", 120);
                  set("enchase/type", "all");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

