// Room: /d/ruzhou/xiaozheng.c 小鎮
// llm 99/02

inherit ROOM;

void create()
{
        set("short", "汝州小鎮");
        set("long", @LONG
這裏已經進入汝州地界了。小鎮不大，但是位於中原驛道旁，南
琿北往的客人便使得這裏慢慢繁榮起來了。甚至使得這裏的本地人口
甚少，到處都是行色匆匆的江湖客人。
LONG
        );

        set("exits", ([
                "southwest" : "/d/nanyang/yidao3",
                "north" : __DIR__"nanmen",
                "east" : __DIR__"shang_road3",
        ]));

        set("objects",([
                __DIR__"npc/xiao-fan" : 1,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
