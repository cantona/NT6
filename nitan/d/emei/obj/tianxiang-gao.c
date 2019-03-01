// tianxiang-gao.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_smear", "smear");
}

void create()
{
        set_name(HIC "天香斷續膏" NOR, ({"tianxiang gao", "gao"}));
        set("unit", "盒");
        set("long", "這是一盒黑色的療傷膏藥，可以擦塗（smear）。\n");
        setup();
}

int do_smear(string arg)
{
        if (!id(arg))  return notify_fail("你擦塗什麼？\n");

        if ( this_player()->qeury("eff_qi") >= this_player()->qeury("max_qi") )
                return notify_fail("搞什麼鬼！？你又沒受傷，用不著塗它！\n");

        this_player()->receive_curing("qi", 250);
        tell_object(this_player(), HIG "你把黑色的膏藥塗在了傷口上，頓時覺的一股清涼之意
流遍全身！\n" NOR );
        destruct(this_object());
        return 1;
}