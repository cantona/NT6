// newbie.c

#include <ansi.h>
#include <command.h>

inherit ITEM;

int do_read(string arg);

void create()
{
        set_name(HIW"新手入門必讀"NOR, ({"book", "newbie book"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是盤古給新手們準備的書，不管你泥齡"
                            "如何，如果進了泥潭務必看看。\n");
        }
        setup();
}

void init()
{
        add_action("do_read", "read");
}
 
int do_read(string arg)
{
        if (! arg || arg != "book")
                return notify_fail("你要讀什麼？要想讀書請輸入(read book)。\n");

        return HELP_CMD->main(this_player(), "feature");
}

