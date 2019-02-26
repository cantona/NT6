//Room: /d/dali/road2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","官道");
        set("long", @LONG
腳下崎嶇的土路穿越川南的山區連接南北，這裏已經進入雲貴，
橫斷山脈延綿聳立，乃是一道天然屏障隔絕南昭和蜀中。繼續向西南
穿過山區，可達大理，北去下山即是天府之國。道路兩旁都是一望無
際的崇山峻嶺(mountain)，和聯綿不絕的大森林(forest)。
LONG );
        set("outdoors", "dalin");
        set("item_desc",([
        "mountain" :
           "中國大西南的橫斷山脈，山勢陡峭，延綿千里，實乃壯哉！\n",
        "forest"   :
           "橫斷山脈最有名的就是這大原始森林了。由於地形太崎嶇，難以採伐，
千年的參天古木覆蓋了整片山區。\n",
        ]));
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : "/d/dali/road1",
            "southwest"  : "/d/dali/road3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19150);
	set("coor/y", -6810);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}