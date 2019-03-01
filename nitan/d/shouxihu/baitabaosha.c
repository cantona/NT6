// Room: /yangzhou/baitabaosha.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","白塔寶剎");
        set("long",@LONG
圓錐形白塔寶剎，由佛教十三層相輪組成，層級高二丈，徑丈許，
剎端置六角形寶蓋，角端懸掛風鈴，每當風起，鈴聲陣陣。寶蓋為青銅
纓絡，上托鎏金黃銅中空葫蘆形寶頂，寶頂高丈許。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "down" : __DIR__"baitafokan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 50);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}