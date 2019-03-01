#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(NOR + WHT "倚天劍" NOR, ({ "yitian jian", "yitian", "jian", "sword" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIY "這便與天下至尊的屠龍寶刀並稱的倚天劍。\n" NOR);
                set("value", 500);
                set("material", "wood");
                set("wield_msg", HIM "$N" HIM "「唰」的抽出$n" HIM "，頓時聞"
                                 "到一股奇異的香味。\n仔細一看，原來這柄倚天"
                                 "劍竟是木頭制成的。\n" NOR);
        }
        init_sword(10);
        setup();
}