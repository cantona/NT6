inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
這裡看來是半山腰了。不遠的前面有一座小石亭，幾位遊客在這
裡歇息。山路到這裡變得十分平坦，東邊的山壁上提滿了名人即興題
下的詩句。遠望山林間層巒迭嶂，滿目滴翠。
LONG );
        set("exits", ([
                "westdown" : __DIR__"shanmen",
                "northup" : __DIR__"shijie9",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}