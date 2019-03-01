inherit ROOM;

void create()
{
        set("short", "花亭");
        set("long", @LONG
你穿過商家堡的後院，來到一個花亭前。花亭以藍色琉璃砌
成。出了花亭，是一條清幽的花徑，兩旁修竹姍姍，花徑鵝卵石
上生滿青苔，顯得平素少有人行。
LONG);
        set("exits", ([
                "west"  : __DIR__"shang_houyuan",
        ]));
	set("coor/x", -6740);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}