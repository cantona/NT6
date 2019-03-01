#include <weapon.h>
#include <music.h>
#include <ansi.h>

inherit SWORD;
inherit MI_QIN;

void create()
{
        set_name(YEL "檀木琴" NOR,({ "tanmu qin", "tanmu", "qin" }) );
        set_weight(9000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一具通體用上等檀木所制的琴。\n" NOR);
                set("unit", "具");
                set("value", 5000);
                set("material", "wood");
                set("wield_msg", YEL "$N" YEL "從背後緩緩取出一具檀木琴合抱在手中。\n" NOR);
                set("unwield_msg", YEL "$N" YEL "將手中的檀木琴收了起來，放到背後。\n" NOR);
                set("stable", 10);
        }
        init_sword(20);
        setup();
}

void init()
{
        add_action("play_qin", "play");
}