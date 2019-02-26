inherit ROOM;

void create()
{
        set("short", "草莓地");
        set("long", @LONG
這裏是白駝山莊後面的一塊草莓地，鮮紅的草莓散落在綠草中，
讓人感到非常美妙愜意。
LONG );
        set("exits", ([
                "northeast" : __DIR__"shulin1",
        ]));

        set("objects" , ([
                __DIR__"obj/caomei" : random(7),
        ]));

        set("outdoors", "baituo");
        set("coor/x", -50010);
        set("coor/y", 19990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}