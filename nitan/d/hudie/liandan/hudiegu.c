inherit ROOM;

void create()
{
	set("short", "蝴蝶谷");
	set("long", @LONG
過了花叢，眼前是一條小徑。但見蝴蝶越來越多，或花或白、或黑
或紫，翩翩起舞。蝴蝶也不畏人，飛近時便在人頭上、肩上、手上停留。
行到過午，只見一條清溪旁結着七、八間茅屋，茅屋之前是幾塊花圃，
種滿了諸般花草。茅屋之後是好大的一片果園，只是看起來一派破敗氣
象，與『蝶谷醫仙』的名頭殊不相稱。
LONG
	);
       set("outdoors", "mingjiao");
       set("no_fight",1);
       set("no_steal",1);
       set("no_beg",1);

	set("exits", 
	([
		"southeast" : "/d/mingjiao/diecong1",
          	"south" : __DIR__"huapu",
          	"north" : __DIR__"guoyuan",

	]));
        set("objects", 
	([
		__DIR__"huqingniu" : 1,
	]));
    
	setup();
}
