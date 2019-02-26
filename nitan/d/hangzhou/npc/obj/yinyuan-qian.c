// yinyuan-qian.c 姻緣籤
// By Alf, Last Update 2002.1130

#include <ansi.h>

inherit ITEM;

void create()
{
    set_name(HIM"姻緣籤"NOR, ({"yinyuan qian", "qian"}));
    set_weight(500);
    if(clonep())
        set_default_object(__FILE__);
    else
    {
        set("unit", "支");
        set("long", HIC"這是一支月老祠內求得的姻緣籤，上面寫着：\n"NOR);
        set("value", 0);
        set("material", "bamboo");
    }
    setup();
}