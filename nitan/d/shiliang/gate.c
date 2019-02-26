// Feb. 6, 1999 by Winder
#include <room.h>
#include <ansi.h>
inherit ROOM;
int do_climb(string arg);
void create()
{
    set("short", "温宅大門");
    set("long", @LONG
這裏就是浙南石樑温家的大門，門口兩個大石獅，威武異
常，大門緊鎖着，門上的銅環卻亮得刺眼。圍牆很高，門匾上
寫着兩個燙金的大字“温府”，果然氣度不凡。門的旁邊有一
株參天大樹(tree),人站在下面很是涼快。
LONG
    );
        set("no_clean_up", 0);
        set("outdoors","shiliang");
        set("exits", ([
                "south" : __DIR__"road1",
        ]));
        set("item_desc", ([
        "tree": "這是一株上百年齡的老樹，枝葉依然十分茂盛，看來是爬不上去的。\n"
        ]) );
        set("coor/x", 1610);
        set("coor/y", -1970);
        set("coor/z", 10);
        setup();
}
void init()
{
    object book, me;
    me = this_player();
    add_action("do_climb", "climb");
}
int do_climb(string arg)
{
    int n;
    n = this_player()->query_skill("dodge");
    if( !arg || arg!="tree" ) {
        write("不要到處亂爬！\n");
        return 1;
    }
    message_vision(
    "$N在古樹前深深地吸了口氣，猛地躍了起來。\n", this_player());
        
    if (n>=80) {
        message_vision("只見$N足尖在樹枝上一點，飛身躍過高牆，已悠然飄落院中。\n", this_player());
        this_player()->move(__DIR__"yuanzi");
    }
    else if (n>=50) {
        message_vision(
        "只見$N雙手在樹上一攀，勉強翻過圍牆，跌落院中。\n", this_player());
        this_player()->move(__DIR__"yuanzi");
    }
    else {
        message_vision(
        "$N高高躍起，可還差一大截呢，看來是輕功不夠好。\n", this_player());
     }
    return 1;
}