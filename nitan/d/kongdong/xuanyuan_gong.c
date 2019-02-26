//1997-3-10 by qyz

inherit ROOM;

//string *things = ({
//            "/clone/misc/chabei",
//            "/clone/misc/chahu",
//            "/clone/misc/hongcha",
//            "/clone/misc/lvcha",
//          "/d/menpai/kongdong/obj/yaochi",
//            });


#include <room.h>


void create()
{
	set("short","軒轅宮");
	set("long",@LONG
走進宮門，正面是高大的彩色三清塑像，周圍放着歷代皇帝舉行祭典時用過
的祭器和樂器，前面放着一個香台，香台上幾根香燭放出微弱的光芒，一陣陣煙
霧從香爐裏裊裊升起，令人如入仙境，正中神龕有二龍戲珠和雙鳳朝儀裝飾，龕
內供奉身着龍袍，腳踏雲履，手捧寶劍的真武坐像。
LONG);
	set("exits",
	([
          "east" : __DIR__"18_yuan",
          "west" : __DIR__"yuhuang_ge",
          "south" : __DIR__"zhaohe_tang",
          "north" : __DIR__"lingzhi_yuan",
          	]));
    set("need_clean","崆峒派");
	set("objects" , ([
		__DIR__"npc/mu" : 1 ,
		__DIR__"npc/song" : 1,
		__DIR__"npc/xia" : 1,
		]) );

    setup();
}
void reset()
{
	string s_obj;
	::reset(); 
	switch(random(5))
	{
	case 0:
		s_obj = __DIR__"obj/yaochi";
		break;
	case 1:
		s_obj = "/d/city/nanyang/obj/book5";
		break;
	case 2:
		s_obj = "/d/city/nanyang/obj/book1";
		break;	
	case 3:
		s_obj = "/d/city/nanyang/obj/book4";
		break;						
	default:
		s_obj = "/d/city/hangzhou/obj/xiang";
		break;
	}
	set("search_things", ([
		"香爐" :  s_obj,
		]) );
}