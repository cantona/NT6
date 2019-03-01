// Room: /d/huanggong/xihuamen.c

inherit ROOM;

void create()
{
        set("short", "西華門");
        set("long", @LONG
西華門是皇帝和後妃們去京西苑囿及回宮時出入皇宮之門. 門外設
有下馬碑石, 碑刻: 官員人等至此下馬. 文武百官到達此地, 文官必須
下轎, 武官必須下馬, 不得違背.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 4 */
                "west"  : __DIR__"humen",
                "east"  : __DIR__"wuying",
                "north" : __DIR__"dao8",
                "south" : __DIR__"dao9",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2840);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}