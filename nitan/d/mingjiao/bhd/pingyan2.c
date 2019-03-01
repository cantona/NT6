// pingyan2.c 綠野
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", GRN"綠野"NOR);
        set("long", @LONG
這裡是島嶼的東部。極目的是一片看不到盡頭的大綠野，是活火
山經幾千萬年的火山灰堆積而成，平野上一群梅花鹿正在低頭吃草，
周圍一片平靜，絕無可怖之處，遠處高山處玄冰白雪，些處卻是極目
青綠，蒼鬆翠柏，更諸般奇花異樹，皆為中土所無。
LONG );
	set("exits",([
		"south" : __DIR__"yanshi",
		"north" : __DIR__"shishan",
                "west" : __DIR__"pingyan3",
                "east" : __DIR__"pingyan4",
	]));
	set("objects",([
		"/d/mingjiao/npc/lu" :  1,
	]));
	set("outdoors","冰火島");
	setup();
}

void init()
{
      string a,b,c;
      a =query("exits/west");
      b =query("exits/north");
      c =query("exits/east");
       set("exits/north", a);
       set("exits/west", c);
       set("exits/east", b);
}
