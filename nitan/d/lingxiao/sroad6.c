#include <room.h>

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG 
走到這裏，反覺暖和一些了，風仍在刮，但耳邊只聽到叮噹
的流水聲。一道白波從巖縫中垂下，簌簌清流令人心神一爽，左
邊熱氣騰騰，煙霧瀰漫，顯然是個温泉，右邊零零落落有幾間木
屋，是凌霄弟子巡山看守時住宿之地。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
            "south"  : __DIR__"sroad5",
            "northup"  : __DIR__"fentianya", 
            "west" : __DIR__"water", 
            "east"  : __DIR__"muwu",
        ]));
        create_door("east", "木門", "west", DOOR_CLOSED);
        set("no_clean_up", 0);
        setup();
}
