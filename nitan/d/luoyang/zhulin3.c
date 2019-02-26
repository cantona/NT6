inherit ROOM;

void create()
{
        set("short", "綠竹林");
        set("long", @LONG
這裏是洛陽東城郊外，好大的一片綠竹叢，迎風搖曳，雅緻天然。你
剛來到這裏，便聽得琴韻丁冬，卻是有人正在撫琴，綠竹林中一片清涼寧
靜，和外面的洛陽城宛然是兩個世界。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"xiaoshe",
                  "west" : __DIR__"zhulin2",
        ]));

	set("coor/x", -6950);
	set("coor/y", 2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}