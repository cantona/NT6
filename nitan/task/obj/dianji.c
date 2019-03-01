#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIG"藏經閣典籍"NOR, ({ "dian ji" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "這可是從少林藏經閣流傳出來的武學典籍。\n");
          }
    set("owner", "無名老僧");
    setup();
}
