// Room: /d/xiangyang/juyifemale.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "女客房");
        set("long", @LONG
這是間整潔的廂房，因門窗常閉著，光線很昏暗。房裡別無他物，
只有兩邊放著幾張收拾得舒舒服服的大床，看著就讓人想睡覺。
LONG );
        set("sleep_room", "1");
        set("no_clean_up", 0);

        set("exits", ([
                "west" : __DIR__"juyihuayuan",
        ]));
        set("coor/x", -7830);
	set("coor/y", -800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}