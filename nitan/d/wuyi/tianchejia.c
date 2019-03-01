// Room: /d/wuyi/tianchejia.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "天車架");
        set("long", @LONG
天車架也稱古崖居，位居丹霞嶂上。是清代咸豐年間三家士紳為逃
避太平軍而在形如城壁的丹霞嶂的十余丈高處建的避難所。避難所建在
一串隙巖洞裡，洞口有小樓半懸空中，洞沿設有圍欄和吊架，可容百余
人。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"path15",
                "south" : __DIR__"path13",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1400);
        set("coor/y", -4900);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
