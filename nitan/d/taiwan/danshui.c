// Room: /d/taiwan/danshui.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "淡水");
        set("long", @LONG
淡水，位於台灣島西北隅，瀕臨台灣海峽，正居台灣第三大河之淡
水河出海口北岸，東南方聳立大屯山系，南面隔河對著觀音山。淡水之
美深具水鄉情調，有“東方那波里”之稱，漢人的市街沿河而建，後轉
築于山坡，斜道起落，梯回階轉之間，極富曲巷幽思。居高眺望河港，
更為美妙，小鎮燈火、下弦之月、飄搖風帆，加上粼粼波光，淡水風光，
其實何止於此！
LONG );
        set("exits", ([
                "east"      : __DIR__"jilonggang",
                "north"     : __DIR__"hongmaocheng",
                "southwest" : __DIR__"zhuqian",
        ]));
        set("objects", ([
                __DIR__"npc/pingpu_kdgl": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2540);
        set("coor/y", -6970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
