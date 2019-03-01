inherit ROOM;

void create()
{
        set("short", "瀟湘館");
        set("long", @LONG
這是縹緲峰靈鷲宮的裁縫室。幾個女子圍坐在一塊，飛針走線，
苦練女紅，為靈鷲宮的諸多女弟子縫紉青衣鬥篷。 
LONG );
        set("exits", ([
                "south" : __DIR__"changl10",
        ]));
        set("objects",([
                CLASS_D("lingjiu") + "/fumingyi" : 1,
        ]));
        setup();
        replace_program(ROOM);
}