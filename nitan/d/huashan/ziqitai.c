inherit BUILD_ROOM;

void create()
{
        set("short", "紫氣台");
        set("long", @LONG
紫氣台終年雲遮霧掩，迷濛不見天日，更為怪異的是：每逢下雨
天，山谷之中就隱隱有紫氣出現。極目四望，風景如畫。在這裏隱居
相必非常愜意。
LONG );
        set("outdoors", "huashan");
        set("exits",([ /* sizeof() == 1 */
            "eastdown": __DIR__"chaopath2",
            "up": "/d/reborn/jitan2",
        ]));
        set("max_room", 3);
        setup();
}
