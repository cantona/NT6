// xiongdong.c 熊洞
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIB"熊洞"NOR);
        set("long", @LONG
此處為一熊洞，洞內極是寬敞，有八九丈深，中間透入一線天光，
宛似天窗一般。此洞以前有幾條白熊在此居處，但後來張翠山夫婦殺
熊而住在此處，故此陶碗、土灶、石牀、粗具等一應俱全。
LONG );
	set("exits",([
		"out" : __DIR__"shishan",
	]));
        set("objects",([
                  "/d/mingjiao/obj/luopan" :  1,
	]));
        set("no_fight", 1);
        set("sleep_room", 1);
	setup();
}
