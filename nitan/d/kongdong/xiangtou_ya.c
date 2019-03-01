//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","象頭崖");
	set("long",@LONG
迎面是一塊巨大的石崖，形狀宛如象頭，此地是以得名“象頭崖”。前面的
山坡上有一棵鬆樹，形如掃帚，名掃帚鬆，因枝幹繁多又叫千頭鬆，東北方向上
一個巨大圓石，石縫中鑲嵌了一株三尺來高的鬆樹，那鬆樹枝幹橫生，虯枝勃發
，人皆稱之探風鬆。
LONG);
	set("exits",
	([
          "west" : __DIR__"juxian_qiao",
          "northup" : __DIR__"xuanhe_dong",
	]));
	set("outdoors","kongdong");
	set("objects", ([
		__DIR__"npc/kdizi2"  : 3,
		]) );
        setup();
        //place_program(ROOM);
}

int valid_leave(object me,string dir)
{
    if(dir=="northup")
      return notify_fail("北上是陡崖，沒法再往上走了。\n");
    return ::valid_leave(me,dir);
}
