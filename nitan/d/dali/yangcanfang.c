//Room: /d/dali/yangcanfang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","養蠶房");
        set("long",@LONG
這是一間擺夷族的桿欄民居，此間下層卻沒有牛羊，三面用竹席
圍住，似一個棚屋，中置數座竹架竹盤，飼養著一些桑蠶。一位擺夷
姑娘正在用新鮮的桑葉喂養桑蠶。
LONG);
        set("objects", ([
           __DIR__"npc/yangcannu": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "west"  : __DIR__"buxiongbu",
        ]));
	set("coor/x", -19010);
	set("coor/y", -6910);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}