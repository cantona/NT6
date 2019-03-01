// wangyun.c 望雲台

inherit ROOM;

#include <ansi.h>
int do_take(string arg);

void create()
{
        set("short", "望雲台");
        set("long", @LONG
這裏就是俠客島最高的 "望雲台" 。在這裏你可以遠望大海，
運氣好的時候還能看見一大奇景-- "雲海" 。在石縫之間長着一顆
松樹，俗稱 "可憐鬆" 。在松樹周圍還頑強的生長着幾顆小草(cao)。
LONG    );
        set("exits", ([
                "northdown" : __DIR__"road8",
        ]));
        set("outdoors", "xiakedao" );
        set("item_desc",([
            "cao" : "幾珠碧綠的小草，你不禁想拿(take)起來。\n"
        ]) );
        set("no_clean_up", 0);
        set("caocount", 1);
        set("coor/x", -3110);
        set("coor/y", -22150);
        set("coor/z", 40);
        setup();
}

void init()
{
        add_action("do_take","take");
}
int do_take(string arg)
{
        object me=this_player();
        object obn;
        int n;
        n = this_player()->query_skill("dodge",1);
        if( !arg || arg != "cao" )
        {
             write("你要拿什麼呀!\n");
             return 1;
        }
message_vision("$N在懸崖前站定，深呼一口氣，突然躍起。\n", this_player());
        if(n >=80)
        {
             if(query("caocount") > 0)
             {
message_vision("只見$N的身子在空中打了幾個盤旋，身子輕飄飄落回，手中多了一物。\n", this_player());
                 obn = new("/clone/medicine/vegetable/fuxincao");
                 obn->move(me);
                 addn("caocount",-1);
             }
             else
message_vision("$N定睛一看，發現草早被人拿走了。\n", this_player());
        }
        else
        {
             me->receive_damage("qi", 50);
             me->receive_wound("qi", 50);
             message_vision(HIR" 只見$N的身子在空中打了幾個盤旋，呀! 不好!!!!\n"NOR, this_player());
             me->move(__DIR__"gudi");
             tell_object(me,HIR"你從懸崖上摔了下來，渾身疼痛，還受了幾處傷。" NOR);
message("vision",HIR"只見"+query("name", me)+"你從懸崖上摔了下來，
躺在地上，半天也不能動。\n" NOR, environment(me), me);
        }
        return 1;
}