// xiaoyuan.c

inherit ROOM;

nosave mapping room_type = ([
        "dule"    : "獨樂居",
        "caihong" : "彩虹居",
        "panlong" : "盤龍居",
]);

void create()
{
        object ob;

        set("short", "小院");
        set("long", @LONG
這裏是一個不大的院子，到處擺放着木料磚瓦。院中坐着一個人，豐
神飄灑，頗具宗匠之風。四周圍着幾個弟子，專心致志的在老師聽課。院
角的一棵樹上掛着一個牌子，上書：代建各種房屋，有意者敬請與魯班洽
談。
LONG );
        set("exits", ([
                "west"  : "/d/nanyang/yidao2",
                "dule"  : __DIR__"dule/xiaoyuan",
                "caihong" : __DIR__"caihong/xiaoyuan",
                "panlong" : __DIR__"panlong/dayuan",
                "east" : "/d/room/playtown/chunzhangjia",
        ]));

        set("outdoors", "city");

        set("objects", ([
                __DIR__"npc/jinlin" : 1,
        ]));

        set("no_fight", 1);
        set("no_sleep_room", 1);

        setup();
        "/adm/npc/luban"->come_here();
}

string query_room_id(string arg)
{
        if (arg && ! undefinedp(room_type[arg]))
                return room_type[arg];

        return 0;
}

void reset()
{
        ::reset();
        "/adm/npc/luban"->come_here();
}
