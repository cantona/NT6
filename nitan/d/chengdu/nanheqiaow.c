// Room: nanheqiaow.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short","南河橋");
        set("long", @LONG
這裡是成都西門外南河橋。府河和南河夾城流過，呵護著這個天
府之國的首府之地。河水清新碧透。東面是西城門，往西就是浣花溪
了。
LONG );
        set("outdoors", "chengdu");
        set("exits",([ /* sizeof() == 1 */
            "west"  : __DIR__"path1",
            "east"  : __DIR__"westgate",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15260);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}