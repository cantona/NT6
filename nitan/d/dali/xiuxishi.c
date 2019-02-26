//Room: /d/dali/xiuxishi.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short", "廂房");
        set("long", @LONG
這是間整潔的廂房，因門窗常閉着，光線很昏暗。房裏別無他物，
只有中間放着幾張收拾得舒舒服服的大牀，看着就讓人想睡覺。這裏
是休息的地方，有時候練功累了，段家弟子也會在這裏休息。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/chahua1",
        ]));
        set("sleep_room", 1);
        set("no_fight", 1);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}