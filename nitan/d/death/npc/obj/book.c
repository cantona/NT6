#include <ansi.h>
inherit ITEM;

void setup()
{}
void create()
{
        set_name(YEL "生死薄" NOR, ({"book"}));
        set("unit", "本");
        set("long", "一本記載人間生死的名冊。\n");
        set("value", 100);
        set_weight(200);
        
        setup();
}