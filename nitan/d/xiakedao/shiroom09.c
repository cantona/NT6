// /d/xiakedao/shiroom09.c 俠客島 石室9
inherit ROOM;
int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
這裏是石洞深處，較為氣悶。此石室內甚是安靜，一名虯髯大漢
和一名道士相對而立，正在緩緩地推手。一人站在遠處牆角，將牆上
的火把取下來擎在手中，緊盯着石壁(wall)，鼻子似乎已經貼了上去。
LONG );
        set("exits", ([
                "south" : __DIR__"shihole3",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「閒過信陵飲」幾個大字。字的下方刻的正是「俠客
行」詩中三人飲酒的故事。只見一人劍眉入鬢，高冠華服，卻坐在下
首相陪，不問可知是信陵君; 另一人乾瘦白鬚，乃是侯嬴。第三人是
背影，肩寬膀闊。圖畫之側小注無數。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3090);
        set("coor/y", -25290);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"