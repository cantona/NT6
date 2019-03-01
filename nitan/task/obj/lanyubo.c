#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIC"藍玉砵"NOR,({ "lanyu bo", "bo" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "只");
            set("material", "stone");
            set("long", "一只藍田美玉精制而成的藥砵，雖然使用日久，但絲毫沒有破痕。藥砵裡\n殘留了微量劇毒, 然已足夠毒死偷寶之人。\n");
          }
    set("owner", "買賣提");
    setup();
}
