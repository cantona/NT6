// /d/yixing/cldamen.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;
#include <ansi.h>

void create()
{
  set("short", "大門");
  set("long", @LONG
這裡便是威鎮江南的長樂幫總舵所在。那長樂幫在江湖上聲勢非同
小可，近年來更是日漸興旺。兩扇紅漆大門上釘著猙獰的虎頭，幾個滿
臉橫肉的幫眾站在兩側。門上有一個大匾(bian)，兩盞氣死風燈來回搖
擺。旁邊有一座碑(bei) ，上面刻著一些文字。
LONG );

  set("exits", ([
    "enter" : __DIR__"cldating",
    "south" : __DIR__"shulin4",
  ]));

  set("item_desc",([
    "bian" : 
"    ※※※※※※※※※※※※※※※※※※※\n"
"    ※※※※　　　　　　　　　　　※※※※\n"
"    ※※※※　　長　　樂　　幫　　※※※※\n"
"    ※※※※　　　　　　　　　　　※※※※\n"
"    ※※※※※※※※※※※※※※※※※※※\n",
      "bei" :
"    長樂，據傳出自唐李頎詩：“莫是長安行樂處，空令歲月易蹉跎。”\n"
"    長樂幫原是江湖上不入流的小幫，從第七代幫主時，開始聲名鵲起。\n"
"    幫中自幫主、總管以下，分為龍靈堂，獅敏堂，熊威堂，虎猛堂和豹\n"
"    捷堂，其分舵更是遍布各地，好手如雲。長樂幫行事亦正亦邪，陰魂\n"
"    不散，黑白兩道人物無不避讓三分。正如市井小兒歌謠雲：長樂無常，\n"
"    無常長樂。\n",
  ]));

  set("objects",([
    __DIR__"npc/cl_qiu" : 1,
  ]));
  set("outdoors", "yixing");

        set("coor/x", 280);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
  object ob;

  me = this_player();
  if( dir == "enter" &&
      objectp(ob = present("qiu shanfeng", environment(me))) &&
      living(ob) &&
       query("family/family_name", me) != HIC"長樂幫"NOR && 
      !query_temp("changle", me) )
    return notify_fail("邱山風攔在你面前，說道：你他媽的怎麼連一點江湖規矩都不懂？起碼也得孝敬一下老子。\n");
  else
    {
//      me->delete_temp("changle");
      return ::valid_leave(me, dir);
   }
}