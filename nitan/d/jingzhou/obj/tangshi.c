//Edited by fandog, 02/15/2000
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(YEL"唐詩選輯"NOR, ({"tangshi book","book","tangshi"}));
        set_weight(1500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一本紙頁發黃的古書，裏面還夾着幾張做鞋和繡花的紙樣。\n");
                set("unit", "本");
                set("material", "paper");
        }
        setup();
}
