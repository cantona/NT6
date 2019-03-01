// edemote.c emote編輯器

#include <ansi.h>

inherit ITEM;
inherit F_AUTOLOAD;

void create()
{
        set_name(HIC "表情動詞編輯器" NOR, ({"emote editor", "editor"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "架");
                set("long", "這是一架看起來怪怪的儀器，上面貼著說明(help editor)。\n");
                set("value", 1);
                set("no_sell", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

int do_help(string arg)
{
        if (! arg || ! id(arg))
                return notify_fail("你要看什麼幫助？\n");
        write (@HELP
關于表情動詞編輯器的說明：

可以使用的命令包括 edemote、cpemote、rnemote，具體請參見這
些命令的幫助。

HELP );
        return 1;
}
