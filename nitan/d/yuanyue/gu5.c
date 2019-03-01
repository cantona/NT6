// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h>

void create()
{
        set("short", "大堂");
        set("long", @LONG
明豐高軒，玉壁生輝。堂中一處白玉塌，塌前一張矮幾上散置著
四時鮮花、各色佳果。四處明潔如鏡，你的身影都映入畫中。
LONG );
        set("exits", ([ /* sizeof() == 4 */ 
                "eastup" : __DIR__"gu4", 
        ])); 
        set("objects",([
                CLASS_D("mojiao/qingqing") : 1,
                CLASS_D("mojiao/dingpeng") : 1,
        ]) );
        set("coor/x",80);
        set("coor/y",10);
        set("coor/z",-20);
        setup();
        create_door("eastup","玉門","westdown",DOOR_CLOSED);
}  
