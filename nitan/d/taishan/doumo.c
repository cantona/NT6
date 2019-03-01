// Room: /d/taishan/doumo.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "鬥母宮");
        set("long", @LONG
鬥母宮為泰山古道觀。宮東臨龍泉峰，又有龍泉水自西北山峽繞宮
東注中溪，故又名龍泉觀。宮築于盤道旁深壑絕壁之上，深秀幽雅。清
康熙初年尼姑住持，祀北鬥眾星之母，遂更名鬥姥宮，又名妙香院，俗
稱鬥母宮。正殿原祀鬥母神，俗稱千手千眼佛。今置地藏菩薩銅像。
    上了前面這一段山路，遊人一般都會在這裡稍為休息。這裡的地勢
已經比泰山鄰近的徂徠山為高，從這裡往東上去便是石經峪。
LONG );
        set("exits", ([
                "southeast" : __DIR__"feilong",
                "southwest" : __DIR__"fengyue",
                "northup"   : __DIR__"tianshen",
                "eastup"    : __DIR__"jingshi",
                "southdown" : __DIR__"taohua",
        ]));
        set("objects",([
                __DIR__"npc/jian-ke" : 1,
        ]));
        set("coor/x", 70);
	set("coor/y", 130);
	set("coor/z", 50);
	setup();
        replace_program(ROOM);
}