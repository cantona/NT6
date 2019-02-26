#include <room.h>
#include <ansi.h>

inherit ROOM;
int do_break(string arg);

void create()
{
    set("short", "莊府大門");
        set("long", @LONG
這裏就是文士莊允城的舊居。自從他被朝廷抓走後，這裏好像就
沒有人住了。一扇大門(men)緊鎖着， 周圍是高高的圍牆(wall)。一
切都很乾淨，並沒有積多少灰塵。
LONG );
    set("exits", ([
        "south" : "/d/beijing/zhuang2",
    ]));
    set("item_desc", ([
        "men" : "這扇門是鎖着的，除非你打破(break)它。\n",
    ]) );
	set("coor/x", -2780);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
}

void init()
{
    object book, me;
    me = this_player();
    add_action("do_break", "break");
}

int do_break(string arg)
{
    int n;
    n=query("neili", this_player());
    if (! arg || arg != "men")
    {
        write("不要隨便打碎別人的東西！\n");
        return 1;
    }


    message_vision("$N走到門前，深吸一口氣，雙掌同時拍出。\n",
                   this_player());
        
    if (n >= 200)
    {
        message_vision("$N只聽一聲轟響，$N把門震開了！\n",
                       this_player());
        set("exits/north", "/d/beijing/zhuang5");
        set("neili", n-200, this_player());
        remove_call_out("close");
        call_out("close", 5, this_object());
    } else
    {
        message_vision("$N大吼一聲“開！”，結果什麼也沒發生。"
                       "看來$N的內力不夠強。\n", this_player());
        set("neili", 0, this_player());
    }

    return 1;
}