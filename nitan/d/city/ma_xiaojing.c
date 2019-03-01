#include <room.h>
inherit ROOM;

void create()
{
        set("short", "小徑");
        set("long", @LONG
小路是用五彩繽紛的石子舖成的。石子組成各種花紋，甚
是好看。路邊池塘裡荷花亭亭，蜻蜓飛來飛去，只有偶爾傳來
的幾聲蛙鳴打破了四周的寧靜。
LONG);
        set("outdoors", "yangzhou");
        set("region", "yangzhou");
        set("exits", ([
                "west"  : __DIR__"ma_lianwu1",
                "east"  : __DIR__"ma_huayuan",
        ]));
        create_door("west", "木門", "east", DOOR_CLOSED);
        set("no_clean_up", 0);
	set("coor/x", 40);
	set("coor/y", -70);
	set("coor/z", 0);
	setup();
}