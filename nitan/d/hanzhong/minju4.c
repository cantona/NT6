// minju4.c 民居
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
這間屋子你一進來就看見屋角大袋小袋地堆滿了糧食，看得出來今
年的收成確實不錯。屋內坐着一位村民，正笑嘻嘻地看着自己的積糧，
也許正在盤算這個冬天又不愁了。
LONG
        );
        set("exits", ([
                "northeast" : __DIR__"guchang",
        ]));

        set("objects", ([
                __DIR__"npc/cunmin" : 1,
        ]));
        set("coor/x", -12280);
	set("coor/y", 830);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}