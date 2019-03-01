#include <ansi.h>
inherit TASK;
void create()
{
    set_name(CYN"唐家家譜"NOR, ({ "jiapu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "張");
            set("material", "paper");
            set("long", "一張唐家家譜\n");
          }
    set("owner", "唐楠");
    setup();
}
