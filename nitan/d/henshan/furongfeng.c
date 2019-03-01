#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "芙蓉峰");
        set("long", @LONG
芙蓉峰是衡山五峰之一，據說芙蓉峰下有個山洞，洞中長滿了芙
蓉花，長年不謝，芙蓉峰也因此得名。但見此處環境清幽，草木蔥綠，
這裡不如祝融峰高，冷暖適宜，實在是個人間仙境。
LONG );

        set("exits", ([
                "southeast"   : __DIR__"shanlu13",
        ]));

        set("objects", ([
                CLASS_D("henshan") + "/liu" : 1,
                CLASS_D("riyue") + "/qu" : 1,
        ]));    

        set("no_clean_up", 0);

	set("coor/x", -6960);
	set("coor/y", -5520);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}