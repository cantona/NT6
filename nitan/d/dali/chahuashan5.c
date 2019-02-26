//Room: /d/dali/chahuashan5.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花山");
        set("long", @LONG
你走在茶花山上，這裏遍地是生長茂盛的茶花。當然，大部分是
凡品，但偶爾也會有一兩株佳品藏匿其中。西望不遠是大理城的北門，
南邊不遠是城牆。
LONG );
        set("objects", ([
           "/d/dali/obj/shanchahua": 1,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "eastdown" : "/d/dali/chahuashan6",
            "west"     : "/d/dali/chahuashan2",
        ]));
	set("coor/x", -19130);
	set("coor/y", -6860);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}