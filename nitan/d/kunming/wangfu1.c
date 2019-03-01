inherit ROOM;

void create()
{
        set("short",  "王府大院" );
        set("long", @LONG
這裡便是平西王府的大院，院內鐘滿了各鐘花草，最顯眼
的卻是中間的一株萬年山茶，巨大的樹幹上開滿了無數的山茶
花，顏色深淺不一，□紫嫣紅，十分好看。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south"    :__DIR__"wangfu",
                "north"   :__DIR__"wangfu2",
                "west"   :__DIR__"xizoulang",
                "east"   :__DIR__"dongzoulang"
        ]));
        set("objects", ([
                "/d/shaolin/npc/shang1" : 1,
        ]));
	set("coor/x", -16840);
	set("coor/y", -7180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);         
}