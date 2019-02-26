// edemote.c emote編輯器
#include <ansi.h>
inherit ITEM;
inherit F_AUTOLOAD;
void setup()
{}
void create()
{
        set_name(HIC "表情動詞編輯器" NOR, ({"emote editor", "editor"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "架");
                set("long", "這是一架看起來怪怪的儀器，上面貼着説明(help editor)。\n");
                set("value", 1);
                set("no_sell", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

void init()
{
        add_action("do_help", "help");
        if (environment() == this_player())
        {
                add_action("do_edemote", "edemote");
                add_action("do_cpemote", "cpemote");
                add_action("do_rnemote", "rnemote");
        }
}

int do_help(string arg)
{
        if (! arg || ! id(arg))
                return notify_fail("你要看什麼幫助？\n");
        write (@HELP
關於表情動詞編輯器的説明：

edemote [-d] [-p] verb
該命令用於編輯，顯示，刪除一個表情動詞。其中verb是表情動詞，
如果使用了-d參數則將刪除該動詞，如果使用了-p參數將顯示該表
情動詞具體的表情描述信息。如果編輯的表情動詞原先是存在的，
則在編輯的時候可以直接輸入"." 以保留原有的相應條目。

cpemote emote1 emote2
該命令可以將第一個表情動詞的描述複製成第二個動詞的描述。復
制的時候原先必須沒有第二個動詞的描述，複製以後第一個動詞的
描述仍然存在，即將有兩個獨立但是描述相同的表情動詞。

rnemote emote1 emote2
該命令可以改掉一個表情動詞的名字，但是描述不變化。

HELP );
        return 1;
}

int do_edemote(string arg)
{
        return "/cmds/imm/edemote"->main(this_player(), arg);
}

int do_cpemote(string arg)
{
        return "/cmds/imm/cpemote"->main(this_player(), arg);
}

int do_rnemote(string arg)
{
        return "/cmds/imm/rnemote"->main(this_player(), arg);
}