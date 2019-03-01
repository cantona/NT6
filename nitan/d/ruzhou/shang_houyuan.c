inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
這裡是商家堡的後院，後院並不大，整個地面全部是用沙石
舖砌。南邊是一條紅木制走廊，通往大廳所在。左邊不時傳來陣
陣撲鼻的飯菜香，原來那裡是廚房所在。
LONG);
        set("exits", ([
                "north"  : __DIR__"shang_lianwun",
                "south"  : __DIR__"shang_zoulang2",
                "east"  : __DIR__"shang_huating",
                "west"  : __DIR__"shang_chufang",
        ]));
        set("objects", ([
                CLASS_D("shang") + "/tai" : 1,
        ]));
	set("coor/x", -6750);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}