#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大門");
        set("long", @LONG
這裏是一處莊正高大石門，與眾不同的是門兩旁各擺着一個
青石雕刻的卧虎，門上還有不少的小孔，也不知道是做什麼用的，
門的正上方的牆裏嵌着一塊石板，石板上刻着“藥王谷”三個蒼
勁的大字，原來這裏就是令武林人士變色的藥王谷。在門的右邊
立着一塊石碑(bei)。
LONG
        );
        set("exits", ([
        "north" : __DIR__"bridge1",
        "east" : __DIR__"lcd07",
        "west" : __DIR__"tiandi1",
        "south" : __DIR__"tiandi2",
]));
        set("item_desc", ([
                "bei" :  HIW"\n     ┏━━┓\n"+
                   HIW"     ┃ "HIB"藥"HIW" ┃\n"+
                   HIW"     ┃ "HIB"王"HIW" ┃\n"+
                   HIW"     ┃ "HIB"谷"HIW" ┃\n"+
                   HIW"     ┃ "HIB"重"HIW" ┃\n"+
                   HIW"     ┃ "HIB"地"HIW" ┃\n"+
                   HIW"     ┃ "HIB"擅"HIW" ┃\n"+
                   HIW"     ┃ "HIB"闖"HIW" ┃\n"+
                   HIW"     ┃ "HIB"者"HIW" ┃\n"+
                   HIW"     ┃    ┃\n"+
                   HIW"     ┃ "HIR"殺"HIW" ┃\n"+
                   HIW"     ┃ "HIR"無"HIW" ┃\n"+
                   HIW"     ┃ "HIR"赦"HIW" ┃\n"+
                   HIW"     ┗━━┛\n"NOR,
        ]));
        set("outdoors", "yaowang");

        setup();
        replace_program(ROOM);
}
int valid_leave(object me, string dir)
{
        if( dir=="north" 
         && query("party/party_name", me) != "藥王谷" )
                return notify_fail(WHT"請看石碑！\n"NOR);
        return ::valid_leave(me, dir);
}