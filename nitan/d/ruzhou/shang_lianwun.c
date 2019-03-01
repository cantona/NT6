inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裡是商家堡廳後的一個練武場，空闊的場地上舖滿了細細
的黃土，正好適合演武。不過這裡雜草叢生，看樣子已經荒廢很
長一段時間了。
LONG);
        set("exits", ([
                "south"  : __DIR__"shang_houyuan",
        ]));
	set("coor/x", -6750);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}