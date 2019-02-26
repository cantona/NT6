// minju3.c 民居
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
這是一所鄉間民居，桌椅都很舊了，而且看得出來是自己敲敲打打
給拼補下來的，不過擦拭得很乾淨。牆壁上斜倚着一支獵叉，也許這家
的主人還是個捕獵高手。
LONG
        );
        set("exits", ([
                "southeast" : __DIR__"guchang",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12280);
	set("coor/y", 850);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}