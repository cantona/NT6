//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","玉皇閣");
	set("long",@LONG
玉皇閣矗立在山顛，是崆峒山最高的建築，稱為“觀頂”，基礎用巨石砌起
異常牢固，在靠近山顛的地方有一大黑石塊，表面平坦，上有石桌石墩，周圍環
以石欄，相傳昔時常有仙人羽客棲集於此，路旁有一巨石，踞另一垣石之上，令
人有飛來之感。閣內一座金碧輝煌的鐘樓，屹立在鬱葱的密林中，或於晨霏中隱
現，若飄渺之天上宮闕，堪為大觀。
LONG);
	set("exits",
	([
	"east" : __DIR__"xuanyuan_gong",
          	]));
        set("outdoors","kongdong");
	set("objects", ([
		__DIR__"npc/kdizi1" : 2,
		]) );
        setup();
        //place_program(ROOM);
}
