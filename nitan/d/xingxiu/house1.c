// /d/xingxiu/house1.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "巴依家客廳");
        set("long", @LONG
這是巴依家的客廳。地上舖著波斯地毯，木架上擺著中原的瓷器。
看得出這家的主人一定很有錢。
LONG );
        set("exits", ([ 
            "west" : __DIR__"house",
        ]));
        set("objects", ([
                __DIR__"npc/afanti": 1
        ]) );
//        set("no_clean_up", 0);
        set("outdoors", "xiyu");

        set("coor/x", -38800);
        set("coor/y", 13000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}