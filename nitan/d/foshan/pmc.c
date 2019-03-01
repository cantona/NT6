#include <ansi.h>
#include <command.h>

inherit ROOM;

int do_look(string arg); 

void create()
{
    set("short", "英雄會館後廳");
        set("long", @LONG
英雄會館乃是佛山大豪「南霸天」鳳天南的家業。常來這裡的人，
都是有能耐有來頭的。現在英雄會館裡正圍著黑壓壓的一大群人，都
是來自各地的知名商賈。鳳天南座于中堂，犀利的目光似乎要把你刺
透一般。西牆掛著的牌子 (paizi)上面寫著此次拍賣大會的規則，一
定要好好看看。
LONG );
        set("no_fight", 1);
        set("no_sleep", 1);

        set("exits", ([
                "north" : __DIR__"pm_restroom",
        ]));

        setup();
        "/adm/npc/feng"->come_here();
}

void init()
{
        object me = this_player();

        if (wiz_level(me) >= 3
            && !query_temp("to_pmc", me) )
        {
                tell_object(me, WHT "\n鳳天南在你的耳邊悄聲說道：巫師操"
                                "作手冊(" HIY "board" NOR + WHT ")就在這"
                                "裡，你老人家可以看看。\n\n" NOR);
                set_temp("to_pmc", 1, me);
        }
        add_action("do_look", "look");
}

int do_look(string arg)
{ 
        object me = this_player();

        if (arg != "paizi" && arg != "board")
                return 0;

        if (arg == "paizi")
                return HELP_CMD->main(me, "pm1");
        else
                return HELP_CMD->main(me, "pm2");
}