//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","招鶴堂");
	set("long",@LONG
招鶴堂是崆峒派迎送客人的地方，地面上鑲嵌有綠色的太極圖案圓盤石，俗
稱“迎送石”，堂內正中供奉著塑金的張天師聖像，端坐雙龍椅，手持斬妖劍，
雙目炯炯，神情嚴肅，兩旁分置十八般兵器。影壁上是一副“鶴鹿鬆猴”浮雕
巨畫，象征高官厚祿。從這裡往裡進去就是軒轅宮。
LONG);
	set("exits",
	([
	"west" : __DIR__"zhaitang",
          "south" : __DIR__"tingyuan",
          "north" : __DIR__"xuanyuan_gong",
	]));
	set("need_clean", "崆峒派");
	set("objects", ([
		__DIR__"npc/chen" : 1,
		]) );
        setup();
	//place_program(ROOM);
}
