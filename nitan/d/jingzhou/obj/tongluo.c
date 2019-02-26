//Edited by fandog, 02/15/2000
#include <ansi.h>
inherit ITEM;
int do_play(string arg);

//void setup()
//{}

void init()
{
        add_action("do_qiao", "qiao");
}

void create()
{
        set_name(HIY"銅鑼"NOR, ({"tongluo"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "面");
                set("long", "這是一面武漢產的銅鑼。你可以敲敲(qiao)它。\n");
                set("value", 100);
        }
//        setup();
}

int do_qiao(string arg)
{
        if (!id(arg))
                return notify_fail("你要敲什麼？\n");
        switch( random(2) ) {
                case 0:
                        say(this_player()->name() + "敲了敲銅鑼，鏜～～～，把你嚇了一跳。\n");
                        write(this_player()->name() + "敲了敲銅鑼，鏜～～～，把旁邊的人嚇了一跳。\n");

                        break;
                case 1:
                        say(this_player()->name() + "使勁敲敲銅鑼：咣～～～，真是震耳欲聾。\n");
                        write(this_player()->name() + "使勁敲敲銅鑼：咣～～～，真是震耳欲聾。\n");

                        break;
        }
        return 1;
}
