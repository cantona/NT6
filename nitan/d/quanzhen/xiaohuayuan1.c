// xiaohuayuan1.c 小花園
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "小花園");
        set("long", @LONG
這裡是重陽觀裡的小花園，空氣中飄著一股鮮花的香味。再往
北去，就是金魚池了。這個花園不大，卻是全真弟子練功間隙最愛
來遊玩的地方。園中見不到一根雜草，也許專門有人負責管理這裡。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "southwest" : __DIR__"houtang3",
                "northeast" : __DIR__"xiaohuayuan2",
        ]));

        set("objects", ([
                __DIR__"npc/zhangyuan" : 1,
        ]));

        set("coor/x", -2730);
        set("coor/y", 120);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}
