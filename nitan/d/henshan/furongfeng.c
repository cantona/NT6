#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "芙蓉峯");
        set("long", @LONG
芙蓉峯是衡山五峯之一，據説芙蓉峯下有個山洞，洞中長滿了芙
蓉花，長年不謝，芙蓉峯也因此得名。但見此處環境清幽，草木葱綠，
這裏不如祝融峯高，冷暖適宜，實在是個人間仙境。
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