#include <room.h>
inherit TRANS_ROOM;

void create()
{
mapping map_short = ([
         "beijing"     : "北京",

]);

mapping trans_pay = ([
         "beijing"     : 300,
]);

      set("short","馬廄");
      set("long",@LONG
這是關外的馬廄，關外苦寒之地，頗乏新鮮草料。但東北大漢慣能吃
苦，馬夫們會把馬牽到馬廄好生照看，將它們喂飽飲足，再洗刷得幹乾凈
凈，一直伺候到客人上路。馬廄雪披下的木柱上釘著一塊破木牌(paizi)。
LONG);
      set("exits",([
                "east"      : __DIR__"kedian",
      ]));
      set("outdoors", "guanwai");
      set("no_fight", 1);
      set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
      ]));
        set("trans", map_short);
        set("trans_money", trans_pay);

      set("coor/x", 3970);
	set("coor/y", 9240);
	set("coor/z", 0);
	setup();
      replace_program(TRANS_ROOM);
}