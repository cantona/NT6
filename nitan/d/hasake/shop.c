// shop.c 哈薩克小店 

inherit ROOM;

void create()
{
        set("short", "哈薩克小店");
        set("long", @LONG
這座帳篷略顯破舊，似乎搭好後主人就沒再修整過它。帳篷邊到是掛
了不少東西，牛皮筋，鈴鐺等等，看來這裏是個小雜品點。
LONG);
        set("exits", ([            
            "south" : __DIR__"pmchang",
            "east" : __DIR__"road1",
            "northwest" : __DIR__"sroom",
            "southeast" : __DIR__"caoyuan3",
        ]));        

        set("objects", ([
                    __DIR__"npc/dealer" : 1,
                    "/d/xingxiu/npc/trader" : 2
        ]));

        set("outdoors", "hasake");
        
        setup();
        replace_program(ROOM);
}