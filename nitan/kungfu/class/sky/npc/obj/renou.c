#include <ansi.h>
inherit ITEM;

void setup()
{}
void create()
{
      set_name(YEL "人偶" NOR, ({"renou"}));
      set("unit", "塊");
      set("long", "一塊未完工的木偶，但已經可以辨認出是個女子的雕像。\n");
      set("value", 0);
      set_weight(200);
        
      setup();
}
