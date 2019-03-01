// Obj: /d/ruzhou/npc/obj/marry-book.c 結婚須知
#include <ansi.h>

inherit ITEM;

void init()
{
        add_action("do_read", "fan");
}

void create()
{
        set_name("《結婚須知》", ({ "jiehun xuzhi", "xuzhi"}));
        set("weight", 600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("value", 500);
                set("material", "paper");
                set("long", "這本書上寫着本MUD結婚的程序，你可以翻閲(fan)它。\n");
        }
        setup();
}

int do_read(string arg)
{
    if (!arg||(arg!="jiehun xuzhi"&&arg!="xuzhi"))
        return notify_fail("你沒有這本書，亂翻口袋幹什麼？\n");
    this_player()->start_more(read_file("/doc/help/marry"));
    return 1;
}
