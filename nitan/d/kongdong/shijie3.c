//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","石階");
	set("long",@LONG
這裏石峽壁立，險峻異常，腳下有一條前人在無路可攀的陡壁上，耗盡心血
，用崖壁上堅硬無比的石頭砌成的一級級石階，石階的兩旁立着一棵棵石柱，上
面連着一條粗如兒臂的鐵鏈，遊人們就只有倚着這條鐵鏈方敢沿着石階上下。古
人曾有詩歎耶：“一寸進一步，天門攀鐵柱。自向此間行，才得上天路。”可見
此山之險。
LONG);
	set("exits",
	([
          "southdown" : __DIR__"shangtian_ti",
          "westup" : __DIR__"shijie4",
	]));
        set("outdoors","kongdong");
        setup();
        //place_program(ROOM);
}
