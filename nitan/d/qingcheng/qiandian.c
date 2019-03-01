// Room: /qingcheng/qiandian.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "鬆風觀");
        set("long", @LONG
這裡是鬆風觀前殿。鬆風觀是青城派總所，青城派威鎮川中，以其
人才輩出之故。當今掌門人余滄海道長，雖其貌不揚，身形矮小，卻是
青城一代宗師。殿中左右分列四大天王，手中分執劍、琵琶、傘、蛇四
樣法器(faqi)，代表了風調雨順的凡民宿願。
LONG );
        set("item_desc", ([
                "faqi" : "
以劍鋒之鋒的諧音喻“風”
以琵琶需常調弦通“調”
以傘為雨具推及“雨”意
以蛇之靈動順暢寓“順”之韻

",
        ]));
        set("exits", ([
                "southdown" : __DIR__"shangqing",
                "north"     : __DIR__"zhongmen",
        ]));
        set("objects", ([
                CLASS_D("qingcheng")+"/yu" : 1,
        ]));
        set("coor/x", -8080);
        set("coor/y", -870);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}