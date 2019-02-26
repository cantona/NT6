// Room: /d/huanggong/taihedian.c
inherit ROOM;

void create()
{
        set("short", "太和殿");
        set("long", @LONG
這就是金鑾寶殿. 硃紅殿柱, 彩繪棟樑, 琉璃瓦頂, 在陽光之下, 
真是燦爛輝煌. 大殿正中的鏤空精雕鎦金龍椅, 不用説也知道就是九龍
寶座. 寶座周圍是六根瀝粉金漆的蟠龍柱, 御座前有造型美觀的仙鶴和
爐鼎. 座後是精雕細刻的圍屏. 每日皇在此上朝問政, 治理天下. 據説
這龍椅居於大地正中, 你儘可量量看.
LONG
        );
        set("exits", ([
                "north"     : __DIR__"zhonghedian",
                "south"     : __DIR__"taiji",
                "east"      : __DIR__"yongxiang3",
                "west"      : __DIR__"yongxiang2",
        ]));
	set("coor/x", -2800);
	set("coor/y", 7741);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}