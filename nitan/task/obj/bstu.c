#include <ansi.h>
inherit TASK;
void create()
{
    set_name( WHT "巴山圖" NOR, ({ "bstu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "張");
            set("material", "paper");
            set("long", "一張詳細的巴山地圖，左下角寫了一行小字：
            成都東十里，左三右四，子午雙時．．\n");
          }
    set("owner", "馬超興");
    setup();
}
