inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short", "居室");
        set("long", @LONG
這裡是柯萬仞的房間。柯萬仞喜歡收集武器，房間四壁都掛
滿了形形色色的刀劍，從倭刀到西洋劍，應有盡有。床邊還掛了
一柄奇怪的東西，聽說是前年從西域來的番人送給他的火槍。據
說老爺子想試試這家伙的威力，結果在床上躺了一個月。
LONG);
        set("exits", ([
                    "south"  : __DIR__"zoulang2", 
        ]));
        set("objects", ([  
                CLASS_D("lingxiao") + "/kewanjun" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
