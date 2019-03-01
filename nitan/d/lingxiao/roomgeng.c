inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short","居室");
        set("long",@LONG 
這是一間安靜的居室，是凌霄城第六代弟子耿萬鐘的房間。
桌上放著一卷《冰雪心法》，牆上掛著一柄劍。束束陽光從窗
格中射入，照在牆上，映得一副《萬裡江山圖》分外雄偉。
LONG);
        set("exits", ([
            "south"  : __DIR__"zoulang1", 
        ]));
        set("objects", ([  
                CLASS_D("lingxiao") + "/gengwanzhong" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
