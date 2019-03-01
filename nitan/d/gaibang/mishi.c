// Room: /d/snow/herbshop1.c

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "密室");
        set("long", @LONG
這是一間光線陰暗的密室，從地上厚厚的灰塵看得出來這裡很少有
人出入，靠西邊的地上放著一副腳鐐，連著一條鐵鏈鑲在牆上，不知道
是用來鎖什麼人，南面的牆(wall)是用紅杉木做的，跟另外三面的灰土
牆比起來顯得有些不尋常。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"chuchang",
        ]));
        set("item_desc", ([
                "wall" : "一堵斑剝淋漓的牆。\n",
        ]));
        set("objects",([
                CLASS_D("gaibang") + "/bai-shijing" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", -10);
        set("coor/z", -30);
        setup();
}

void init()
{
        add_action("do_move", "push");
        add_action("do_move", "break");
}

int do_move(string arg)
{
        object paper, me=this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "wall")
        {
                if( !query("had_staffbook") && query("neili", me)>200 )
                {
                        message_vision("$N運足內力猛向破牆拍去，只聽嘩得一"
                                       "陣響，牆頂落下來一本破紙...。\n",
                                       this_player());
                        paper = new("/clone/book/staff_book");
                        paper->move(__FILE__);
                        set("had_staffbook", 1);
                        return 1;
                }
                message_vision("$N狠狠一頭撞在牆，眼前頓時鮮紅一片...\n",
                               this_player());
                this_player()->receive_damage("qi", 30);
                return 1;
        }
        return 0;
}
