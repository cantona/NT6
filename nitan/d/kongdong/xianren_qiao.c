//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","仙人橋");
	set("long",@LONG
這裏是兩座孤崖之間唯一的通道－－“仙人橋”，前人在石面光滑如削的絕
壁上鑿出僅一腳一手深的石窩或淺窄的石級，一直通向崖壁的幾個石洞，洞旁有
“羅立諸峯”，“明星玉女”等引人注目的題刻，古時真人就是在這裏修行，可
謂絕世脱俗。再往上就是“疑無路”了。
LONG);
	set("exits",
	([
          "east" : __DIR__"lianhua_tai",
          "up" : __DIR__"yiwu_lu",
          	]));
        set("outdoors","kongdong");
        setup();
        //place_program(ROOM);
}
