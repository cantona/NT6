//1997-3-10 by qyz
#include <room.h>

inherit DOOR_ROOM;



void create()
{
        set("short","蓮花台");
        set("long",@LONG
這裡是崆峒山的絕頂，孤峰聳峙，獨秀霞表，相傳為黃帝授道壇，右邊就是
萬丈深淵，在此登高一呼，眾山皆應，放眼四望，崆峒數百裡，羅列眼前，如拱
如揖，似碧浪起伏，勢皆東傾。當晴霽黎明，觀看日出，最為奇觀。
LONG);
        set("exits",
        ([
          "south" : __DIR__"lingzhi_yuan",
          "west" : __DIR__"xianren_qiao",
                ]));
        create_door("south",([
                                "name" : "小木門",
                                "lock" : "lock001",
                                "status" : 3,
                                "id"  : ({ "south","小木門","door",}),
                                "other_side_dir" : "north",
                                ]),
                        "north");
        set("outdoors","kongdong");
        setup();
}

void reset()
{
        if( !random( 5) )
        set("objects", ([
                                __DIR__"npc/wuming" : 1,
                ]) );
        ::reset();
}
