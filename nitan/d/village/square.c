inherit ROOM;

void create()
{
        set("short", "打谷場");
        set("long", @LONG
這裡是村子的中心，一個平坦的廣場，每年秋收打谷就在這。廣
場東角有棵大槐樹，平日茶余飯後，村裡的男女老少都愛聚在這裡談
天說地。角上有幾個大谷堆。
LONG );
        set("exits", ([
                "northwest" : __DIR__"nwroad2",
                "south" : __DIR__"sroad4",
                "east"  : __DIR__"eroad3",
        ]));
        set("objects", ([
                __DIR__"npc/kid": 2,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "village");
        setup();
        replace_program(ROOM);
}