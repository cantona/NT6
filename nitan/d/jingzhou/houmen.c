inherit ROOM;

void create()
{
        set("short", "後門");
        set("long", @LONG
這裏是關帝廟的後門，朝望北去，不遠處是一個小山坡。
LONG );
        set("exits", ([
                "south" : __DIR__"houdian",
                "northup" :__DIR__"xiaoshan",
        ]));

        set("coor/x", -7120);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}