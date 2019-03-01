//Room: /d/dali/langan3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","小桿欄");
        set("long",@LONG
一間擺夷族的桿欄民居，此間下層沒有牛羊，卻用竹席圍成一個養
桑蠶的小棚屋，有竹架竹盤。樓上傳來陣陣紡紗機的梭飛聲。
LONG);
        set("objects",([
            __DIR__"npc/yangcannu" : 1,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "west"   : __DIR__"nongtian5",
            "up"     : __DIR__"langan4",
        ]));
	set("coor/x", -19010);
	set("coor/y", -6900);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}