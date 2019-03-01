// Room: /d/xiangyang/anfugate.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "安撫使衙門");
        set("long", @LONG
這是安撫使衙門的大門，銅皮包門似乎極為沉重，上面有兩個明
晃晃的銅環；大門緊閉，裡面卻傳出一陣陣嬉笑聲，和門口的肅殺很
不協調。想來這個安撫使大人的日子還是過得蠻滋潤的。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "south" : __DIR__"anfupailou",
        ]));
        set("coor/x", -7820);
	set("coor/y", -750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}