// baizhusipao.c 白苧絲袍

#include <armor.h>
inherit CLOTH;
void create()
{
        set_name("白苧絲袍", ({ "baisi pao", "cloth" }));
        set("long","一套玉色的苧絲袍，裁剪和體，縫製精細。\n");
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "套");
                set("value", 1000);
                set("armor_prop/armor", 2);
                set("armor_prop/per", 2);
        }
        setup();
}
