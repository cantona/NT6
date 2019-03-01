//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "黃鶴樓");
        set ("long", @LONG
黃鶴樓與湖南的岳陽樓、江西的滕王閣並稱江南三大名樓。關于此
樓的來歷有許多傳說：有說古時仙人乘鶴路經此地；有說呂洞賓曾在此
羽化飛仙。但流傳最廣的，是說古時有位道士，一天在左近一家酒肆中
用桔皮畫了只鶴，並告知酒肆主人，如有客人來此飲酒，只要一拍手，
鶴即翩然起舞，以助酒興。此後，來此飲酒的客人越來越多，酒肆生意
格外興隆。十年後，道士復至，拈奏鐵笛，但見白雲飛來，鶴亦飛舞，
道人遂駕鶴而去。酒肆主人為了紀念這位道士，就在這裡建了一座“黃
鶴樓”。這裡向來是文人薈萃，宴客送友的勝地。東邊是一面湖水，北
面是大江，江中但見一柱石壁擎天。
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "north" : __DIR__"chibi",
                "east"  : __DIR__"donghu",
        ]));
  
        set("no_clean_up", 0);
        set("coor/x", -1400);
        set("coor/y", -2220);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}