#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("礁石", ({"jiao shi", "stone", "shi"}));
        set("unit", "塊");
        set("long", "這是露出海面的礁石，只有容得下一個人站住。\n");
        set_temp("apply/yinshen",1);
        set("value", 1000);
        setup();
}