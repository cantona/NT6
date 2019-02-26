#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "姚春內室");
        set("long", @LONG
這裏是一間小小的房間，沒什麼特別的地方，你看見書桌旁邊有
一位頭髮花白的老人正在閲讀經書，那便是京城回春堂著名的『跌打
名醫』姚春了。姚春的前方有一扇半開的鐵門，不停的從裏面冒出滾
滾濃烈的藥味。
LONG );
        set("no_fight", 1);
        set("objects", ([
                "/d/beijing/npc/liandan_yaochun"     : 1,
        ]));
        set("exits", ([
                "north" : "/d/beijing/liandan_fang",
                "south": "/d/beijing/liandan_neiting",
        ]));

	set("coor/x", -2800);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
}