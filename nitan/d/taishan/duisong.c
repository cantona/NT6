// Room: /d/taishan/duisong.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "對鬆山");
        set("long", @LONG
出朝陽洞北去，便是對鬆山。對鬆山雙峰對峙，古鬆萬株，蒼翠蓊
鬱，層層疊疊，又名萬鬆山、鬆海。雲出其間，天風莽盪，虯舞龍吟，
鬆濤大作，堪稱奇觀。李白有“長鬆入雲漢，遠望不盈尺”的詩句。乾
隆則稱“岱宗窮佳處，對鬆真絕奇”。
LONG );
        set("exits", ([
                "southdown" : __DIR__"chaoyang",
                "northup"   : __DIR__"kaishan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 230);
	set("coor/z", 130);
	setup();
        replace_program(ROOM);
}