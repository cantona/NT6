// Room: /d/fuzhou/yijinfang.c
// Last Modifyed by Evil on Sep. 10 2002

inherit ROOM;

void create()
{
        set("short", "衣錦坊");
        set("long", @LONG
舊名通潮巷。宋代宣和年間(1119—1125年)陸藴、陸藻兄弟居於此
地，兩兄弟才華橫送，名重一時。陸藴官任福州知州，陸藻官任泉州知
州，兩人回鄉時命此坊為“棣錦坊”。南宋淳熙年間(1174—1189年)，
王益樣任江東提刑，退休後也居於此地，將棣錦改名為衣錦，以示衣錦
返鄉之意。 
LONG );
        set("exits", ([
                "east"    : __DIR__"nanhoujie1",        
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -100);
	set("coor/y", -6190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}