//  Room:  /d/luoyang/road2.c

inherit  ROOM;

void  create  ()
{
        set("short",  "大官道");
        set("long",  @LONG
這是一條寬闊筆直的官道，足可容得下十馬並馳。路邊還開着些不
入流的牡丹花，一看就知道是洛陽城的轄地。東面就是通往揚州的大官
道，西面則是著名的洛陽城，而東北面則是著名的旅遊勝地：白馬寺。
寺廟進香的遊客很多，路邊草地已經給踩得相當平了。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"      :  __DIR__"hulaoguan",
                "westup"    :  __DIR__"ebridge",
                "south"     :  __DIR__"road7",
                "northeast" :  __DIR__"baimasi",
                "southeast" :  __DIR__"road0",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6910);
	set("coor/y", 2150);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}