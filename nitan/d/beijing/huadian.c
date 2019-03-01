#include <room.h>
inherit ROOM;

void create()
{
        set("short", "鮮花店");
        set("long", @LONG
這是一個小小的店面，據說這兒的老板是個六十來歲的老頭子，
可是你此時見到的卻是一位年紀輕輕的小姑娘。此時她正在細心的為
客戶挑選花朵，態度非常可人， 臉上的兩個小酒窩裡盛著天真爛漫的
笑容。頓時你也想湊個趣，在她這兒買幾束花。
LONG );
       set("exits", ([
                "south" : "/d/beijing/yong_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/huanv" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}