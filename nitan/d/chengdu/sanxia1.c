#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "西陵峽");
        set("long", @LONG
這裡便是長江三峽的西陵峽，長江兩岸高山聳立，遮天蔽日，真
可謂是猿猴愁末攀啊！由于這裡河道比較窄，河水變的不安起來，發
出陣陣咆哮聲，不時翻滾著旋渦向東流去。
LONG );
        set("exits", ([
                  "west" : __DIR__"sanxia2",
                "southeast" : __DIR__"shudao10",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15090);
	set("coor/y", -1820);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}