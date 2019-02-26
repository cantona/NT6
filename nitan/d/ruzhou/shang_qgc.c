inherit ROOM;

void create()
{
        set("short", "前廣場");
        set("long", @LONG
這裏是商家堡內的一個廣場，整個廣場用沙石鋪砌而成，非
常的乾淨。廣場的北邊有一條青石小徑，可以通過它到達商家堡
的廳內。
LONG);
        set("exits", ([
                "north"  : __DIR__"shang_xiaojin1",
                "south"  : __DIR__"shang_men",
                "west"  : __DIR__"shang_lianwuw",
                "east"  : __DIR__"shang_lianwue",
        ]));
        set("objects", ([
                __DIR__"npc/shang2" : 1,
        ]));
	set("coor/x", -6750);
	set("coor/y", 1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}