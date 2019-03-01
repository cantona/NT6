//山道:shanlu.c 
//tomcat
inherit ROOM;

void create()
{
	set("short", "山道");
	set("long", @LONG
這是一條筆直的山路向前方延伸，一直隱沒于雲霧之中，
不知怎麼這裡的人煙越來越稀少，你不禁暗自嘀咕不會出什
麼事吧？你鼓起勇氣繼續想前走著。

LONG
	);

	set("outdoors", "migong");

	set("exits", ([ /* sizeof() == 3 */
	"west" : __DIR__"zhanchang/entry",
	"east" : "/d/changan/zhongnan",
 ]));

	setup();
	replace_program(ROOM);
}

