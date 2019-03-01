//Room: /d/dali/shilin1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","李子箐石林");
        set("long", @LONG
相傳優人于隆冬遙見石上有李二株，結實鮮紅，晚不及收，次日
尋之不復見，故稱李子箐。面積約一千二百畝，包括大石林，小石林，
和外石林，是路南石林最精華者之一。千峰比肩，大小高矮，較為接
近，遠觀但見一片密密簇簇，似缺少變化躍動，近賞則大不相同，那
神奇的大自然的精雕細琢，使得頑石無論壯鳥，壯獸，或擬人，擬物，
均表情逼肖，疑真還假。
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "east"    : "/d/dali/changhu",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19170);
	set("coor/y", -6800);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}