// gbandao.c 練功房
// by aji
#include <room.h>

inherit ROOM;

void kick();

void create()
{
        set("short", "暗道");
        set("long", @LONG
一條狹窄的地下秘密通道，筆直的朝東面延伸。通道的盡頭有明
亮的光線透進來。
LONG );
        set("exits", ([
		"east" : "/d/city/gbxiaowu",
                "out" : "/d/city/pomiao",
        ]));
	set("objects",([
		CLASS_D("gaibang") + "/jian" : 1
	]));
//	set("no_clean_up", 0);
	create_door("out", "小門", "enter", DOOR_CLOSED);

	set("coor/x", 40);
	set("coor/y", 40);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((!myfam || myfam["family_name"] != "丐幫") && dir == "east" &&
                objectp(present("jian zhanglao", environment(me))))
                return notify_fail("簡長老一把揪住你的衣領說：“慢著！”\n");
        return ::valid_leave(me, dir);
}
