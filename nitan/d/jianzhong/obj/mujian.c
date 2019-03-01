#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
       set_name("木劍", ({ "mu jian", "jian", "sword" }) );
       set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
               set("unit", "把");
               set("long",HIC@LONG
這把劍輕飄飄的渾似無物，是木頭削成的，劍身劍柄都有些腐朽了。
LONG
NOR
);
               set("value", 0);
               set("material", "wood");
                }
       init_sword(10);
              setup();
}