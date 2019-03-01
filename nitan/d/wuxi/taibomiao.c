// Room: /d/wuxi/taibomiao.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "泰伯廟");
        set("long", @LONG
早在遠古時期，泰伯奔吳，在這裡傳授當地人識字、紡織、發展陶
瓷業的冶銅業，和奠定了江南文化的基礎。泰伯也因此受到了當地人民
的敬重和愛戴。人們來此大多放下武器，恭恭敬敬的立于一旁進香磕頭。
如今無錫城發展了，除了逢年初九泰伯誕辰之日外，來這裡的人也不多
見了。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"road9",
                "west" : "/d/guiyun/road1",
        ]));
        set("coor/x", 1010);
	set("coor/y", -790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}