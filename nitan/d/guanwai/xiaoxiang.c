// /guanwai/xiaoxiang.c

inherit ROOM;

void create()
{
        set("short", "小巷");
        set("long", @LONG
這是一個僻靜幽深的小巷，四周寂靜無聲，一個人影也沒有。長長的石
板路上落了一層厚厚的積雪，踩在腳下發出“咯吱”的響聲。小巷的盡頭有
一座土屋。
LONG );
        set("exits", ([
                "south" : __DIR__"tuwu",
                "east"  : __DIR__"beicheng",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "guanwai");
        set("coor/x", 3980);
	set("coor/y", 9250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
