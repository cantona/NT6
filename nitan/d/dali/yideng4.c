//Cracked by Kafei
// yideng quest room 4

inherit ROOM;
void create()
{
        set("short", "山腰");
        set("long", @LONG
這裏是山的半腰，眼前景色如畫，清溪潺潺，水流平穩之極，幾
似定住不動。那溪水寬約丈許，兩旁垂柳拂水，綠柳之間夾植着無數
桃樹，若在春日桃花盛開之時，想見一片錦繡，繁華耀眼。這時雖無
桃花，但水邊生滿一叢叢白色小花，芳香馥郁，綠柳叢間時有飛鳥鳴
囀。山邊一條手臂粗細的長藤，沿峯而上。仰頭上望，見山峯的上半
截隱入雲霧之中，不知峯頂究有多高。
LONG );

    set("no_sleep_room",1);
    set("objects", ([
                CLASS_D("dali") + "/woodcutter" : 1,
        ]));

        set("exits", ([
                "up"  : __DIR__"yideng5",
                "out" : __DIR__"maze1",
        ]));

        set("invalid_startroom", 1);
        set("coor/x", -38000);
        set("coor/y", -80000);
        set("coor/z", 100);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "up" && objectp(present("qiao fu", environment(me))))
        return notify_fail("樵夫一眼不發的擋在你身前。\n");
        return ::valid_leave(me, dir);
}
