#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_QIN;

void create()
{
        set_name(HIC "仲尼式琴·宋朝" NOR, ({ "zhongni qin", "zhongni", "qin" }));
        set_weight(500);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                             
                set("long", HIC "此琴體扁身薄，琴體怪異，琴軫右面垂下深\n"
                                "舌羅漢腿，漆色亮綠，微泛綠光，仲尼式琴\n"
                                "為元朝主流。\n" NOR);
                set("value", 200000);
                set("material", "wood");
             }
        setup();
}

void init()
{
        add_action("play_qin", "play");
}