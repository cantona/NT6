// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "廚房");
        set("long", @LONG
這裏是温家的廚房，温家請的是很有名氣的大師傅負責
打理全家的伙食，温家的師傅在全浙江都是很有名氣的，這
時候還沒到開飯時間，大師傅在那裏坐着吸煙。
LONG
        );
        set("exits", ([
                "east" : __DIR__"zoulang3",                
        ]));
        set("objects", ([
                __DIR__"npc/dashifu" : 1,
        ]));
      
        set("coor/x", 1590);
        set("coor/y", -1920);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
 