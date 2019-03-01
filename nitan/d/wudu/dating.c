inherit ROOM;

void create()
{
        set("short", "大廳");
        set("long", @LONG
這裡是個寬廣的大廳，高大的盤龍柱一人都合抱不過來。這裡是
平日教主召集教眾們議事的地方，大廳正中供奉著五聖--毒蛇，蜘蛛，
蜈蚣，蠍子蟾蜍的畫像。幾位長老正坐在廳中議事 。
LONG);
        set("exits", ([
                "east" : __DIR__"huayuan1",
                "south" : __DIR__"jingshi",
                "west" : __DIR__"lianwu",
                "north" : __DIR__"shufang",
        ]));
        set("objects", ([
               CLASS_D("wudu") + "/qiyunao" : 1,
               CLASS_D("wudu") + "/panxiuda" : 1,
               CLASS_D("wudu") + "/cenqisi" : 1,
               CLASS_D("wudu") + "/first" : 1,
        ]));

        set("valid_startroom", 1);
        setup();
        "/clone/board/wudu_b"->foo();
}
