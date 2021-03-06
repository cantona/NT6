// gbandao.c 練功房
#include <room.h>

inherit ROOM;

void kick();

void create()
{
        set("short", "暗道");
        set("long", @LONG
一條狹窄的地下祕密通道，筆直的朝東面延伸。通道的盡頭有明亮
的光線透進來。
LONG );
        set("exits", ([
                "east" : __DIR__"gbxiaowu",
                "out" : __DIR__"pomiao",
        ]));
        set("objects",([
               CLASS_D("gaibang") + "/jian" : 1,
        ]));
//      set("no_clean_up", 0);
        create_door("out", "小門", "enter", DOOR_CLOSED);

        set("coor/x", 70);
        set("coor/y", 61);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((!myfam || myfam["family_name"] != "丐幫") && dir == "east" &&
                objectp(present("jian zhanglao", environment(me))))
                return notify_fail("簡長老一把揪住你的衣領説：“慢着”\n");
        return ::valid_leave(me, dir);
}