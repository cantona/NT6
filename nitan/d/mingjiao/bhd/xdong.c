// xdong.c 石洞
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIB"石洞"NOR);
        set("long", @LONG
此處為一小山洞，中間透入一線天光，宛如天窗一般。這裏陶碗、
土灶、石牀、廚具等一應俱全。
LONG );
	set("exits",([
		"out" : __DIR__"shishan1",
	]));
        set("objects",([
                CLASS_D("mingjiao") + "/xie" : 1,
	]));
	setup();
}
