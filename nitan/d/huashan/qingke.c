// qingke.c

inherit ROOM;

void create()
{
        set("short", "青柯坪");
        set("long", @LONG
走過崎嶇的十八盤，穿過雲門，就到了青柯坪。青柯坪是一山間
盆地，地勢略為平坦。從這裡開始，上山的路都是由原地鑿出的石階。
遠遠望見一個小小石亭，便是賭棋亭了。相傳宋太祖與華夷先生曾弈
棋于此，將華山作為賭注，宋太祖輸了，從此華山上的土地就不須繳
納錢糧。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "northdown" : __DIR__"yunmen",
                "eastup"    : __DIR__"huixinshi",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huashan" );
        set("objects", ([ 
                "/clone/npc/walker" : 1,
        ]));        

        setup();
        replace_program(ROOM);
}
 