// Feb. 6, 1999 by Winder
#include <room.h>
#include <ansi.h>
inherit ROOM;
int do_jump(string arg);
void create()
{
    set("short", "玫瑰小亭");
    set("long", @LONG
你正站在湖邊的一個小亭裏，通過一條蜿蜒的走廊可以回到
大廳。小亭修築地相當雅緻，在這裏可以欣賞池塘中的荷花和金
魚，亭子北面湖中豎着幾根木樁，遠處的湖中有個小島，朦朧間
看得卻是不太真切。
LONG
    );
    set("no_clean_up", 0);
        set("outdoors", "shiliang");
    set("exits", ([
        "south" : __DIR__"zoulang4",
    ]));
    set("item_desc", ([
        "木樁" : "這是幾根分佈得怪里怪氣的木樁，看上去不是很結實。\n"
    ]) );
        set("coor/x", 1610);
        set("coor/y", -1900);
        set("coor/z", 0);
        setup();
}
void init()
{
    object book, me;
    me = this_player();
    add_action("do_jump", "jump");
}
int do_jump(string arg)
{
    int n;
    n = this_player()->query_skill("dodge");
    if( !arg || arg!="木樁" ) {
        write("不要亂跳，現在是冬天，可不是能游泳的季節哦！\n");
        return 1;
    }
    message_vision(
    "$N深深地吸了口氣，猛地躍了起來。\n", this_player());
        
    if (n>=100) {
        message_vision(
        "只見$N輕輕一躍，穩穩地站在湖中的木樁上，幾下起落，已經到達了湖中小島。\n", this_player());
        this_player()->move(__DIR__"xiaodao");
    }
    else {
        message_vision(
        "$N高高躍起,重重地落在木樁上，結果把木樁踩斷了！“撲通”一聲掉進水中。\n", this_player());
        this_player()->move(__DIR__"huli");
     }
    return 1;
}