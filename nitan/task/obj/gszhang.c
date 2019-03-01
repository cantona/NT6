#include <ansi.h>
inherit TASK;
void create()
{
    set_name("怪蛇杖", ({ "guaishe zhang", "shezhang", "zhang"}));
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "根");
            set("material", "wood");
            set("long", "一根頂部有條怪蛇的蛇杖，蛇頭處有機關，咬起人來厲害無比！\n");
          }
    set("owner", "歐陽鋒");
    setup();
}
