inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這是個美麗的大花園，園子裏面種着鮮豔的紅玫瑰。白衣少女常
來這裏嬉戲。沿着彎彎曲曲的花徑，可以通到山莊的許多地方。東邊
是廚房。西邊是白駝山少主歐陽克的內室，門虛掩着，也不知主人在
不在。
LONG );
        set("outdoors", "baituo");
        set("exits",([
                "west"  : __DIR__"neishi",
                "north" : __DIR__"zhuyuan",
                "east"  : __DIR__"chufang",
                "south" : __DIR__"menlang",
        ]));

        set("objects",([
                __DIR__"npc/whitelady" : 2,
        ]));

        set("coor/x", -49980);
        set("coor/y", 20050);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}