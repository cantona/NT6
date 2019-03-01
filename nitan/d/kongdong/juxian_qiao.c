//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","聚仙橋");
	set("long",@LONG
相傳聚仙橋是八仙聚會的地方，在聚仙橋的中央，有一個二米見方的石台，
三面懸空，周圍環著足有兒臂粗細的鐵鏈，道教信士經常在這裡焚表以祭奠天神
，每逢春夏之交，香客們在登峰進香後，將祭神的表撕成碎片，擲于台下，可看
山谷間千百只飛燕群相爭銜，蔚為奇觀。
LONG);
	set("exits",
	([
	"south" : __DIR__"shijie4",
	"east" : __DIR__"xiangtou_ya",
          "northup" : __DIR__"shanmen",
	]));
        set("outdoors","kongdong");
	set("objects", ([
		__DIR__"npc/youke" : 3,
		]) );
        setup();
        //place_program(ROOM);
}
