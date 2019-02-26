// chongling.c 叢林
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIG"叢林"NOR);
        set("long", @LONG
向北一直走出二十餘里，就是一大片叢林了。原來此島方圓極廣，
延伸至北，不知盡頭。叢林老樹參天，陰森森的遮天蔽日，林內有什
麼古怪，卻是不得而知。遇有好事之人肯定要進入一探的。
LONG );
	set("outdoors","冰火島");
	set("exits",([
		"south" : __DIR__"shishan",
                "north" : __DIR__"cling1",
	]));
	setup();
}
