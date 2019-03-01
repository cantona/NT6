//Created by Redhat@Sjmud 2009/4/7
//updated by Zhuifeng@SJFY 2010/7/27

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "quest/射雕英雄傳/風雪驚變/"

void create()
{
	set("short", GRN "後院" NOR);
	set("long",@long
這裡就是大俠楊鐵心家的後院，院子由籬笆和竹子編成的柵欄，
院子裡有一小塊地種了好幾種蔬菜，菜地旁邊籬笆上靠著一把鋤頭。
long);
  set("indoors", "牛家村");
	set("exits",([
		"south" : __DIR__"yangjia",
		"north" : __DIR__"mafang",
]));
            set("quest",1);
            	            set("objects",([
               __DIR__"npc/yang": 1,
               __DIR__"npc/bao": 1,
            ]));
	//set("no_fight", 1);
	setup();
}


