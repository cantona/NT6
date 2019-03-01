inherit ROOM;  
#include <ansi.h> 

void create()
{
        set("short", "山路");
        set("long", @LONG
越往上走，寒氣癒甚，霜雪漫天紛紛而下。極目遠望，只見
滿天雪白，萬物晶瑩。不遠處似乎有個湖泊，山泉瀑布奔騰入湖，
綠樹叢中馥鬱的鮮花爭妍鬥艷，讓你不由得加快腳步。路旁結滿
了一條條冰柱，倒垂而下，鋒利尖銳，有時凌霄弟子練劍之時也
將其作為兵器使用。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "southdown"  : __DIR__"sroad4",
                    "north"  : __DIR__"sroad6",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("no_clean_up", 0);
        set("ice_count", 5);
        setup();
        replace_program(ROOM);
} 