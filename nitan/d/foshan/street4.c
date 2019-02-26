inherit ROOM;

void create()
{
        set("short", "東鎮街");
        set("long", @LONG
鳳家在佛山是首屈一指的大户，鳳家的家丁常牽着狼狗魚肉鄉里。
一般的百姓只好忍辱偷生。一條大街橫亙東西。路南一家三開間門面
的大酒樓，招牌上寫着「英雄樓」三個金漆大字，兩邊敞着窗户，酒
樓裏刀杓亂響，酒肉香氣陣陣噴出。路北有家燒餅油條鋪，裏面傳出
陣陣油煙香氣。
LONG );
        set("objects", ([
                "/clone/quarry/gou2" : 2,
                __DIR__"npc/zhongxiaoer" : 1,
                __DIR__"npc/zhongsisao"  : 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "north" : __DIR__"youtiaopu",
                "south" : __DIR__"yingxionglou",
                "west"  : __DIR__"street3",
                "east"  : __DIR__"street5",
        ]));
	set("coor/x", -6560);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}