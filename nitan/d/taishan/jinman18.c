// Room: /d/taishan/man18.c
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "緊慢十八盤");
        set("long", @LONG
你走在不緊不慢十八盤上，兩腿發軟，揮汗如雨。兩邊是光禿的巖
壁，無處可以遮風避日。十八盤的兩山崖壁如削，陡峭的盤路鑲嵌其中，
遠遠望去，恰似天門雲梯。回頭看看，人行如蟻，盡在腳下。上頭離南
天門還好遠呢。泰山之雄偉，盡在十八盤；泰山之壯美，盡在攀登中！ 
LONG );
        set("exits", ([
                "northup"   : __DIR__"shengxian",
                "southdown" : __DIR__"longmen",
        ]));
        set("objects", ([
                __DIR__"npc/tiao-fu" : 1,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 270);
	set("coor/z", 170);
	setup();
        replace_program(ROOM);
}