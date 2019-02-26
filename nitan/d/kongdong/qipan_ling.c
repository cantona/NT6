//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","棋盤嶺");
	set("long",@LONG
這裏巨石甚多，形狀怪異，崖上大石怪突，洞穴奇特，內有石室，石門，石
牀，石凳等，傳為上古魯真人修煉之所，道士趙真人曾臨崖邊，與一仙人對弈，
仙人予一棋子令吞，即成仙去，今嶺上還有下棋石之遺蹟。
LONG);
	set("exits",
	([
          "east" : __DIR__"shanmen",
	"west" : __DIR__"zixiao_ya",
          	]));
          	set("need_clean", "崆峒派");
        set("outdoors","kongdong");
        setup();
        //place_program(ROOM);
}
