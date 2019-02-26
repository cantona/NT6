// /d/beihai/yilan.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "漪瀾堂");
        set("long", @LONG
漣漪堂與北岸五龍亭隔水相望，其上層兩側之廊折下，形成一獨特
形式之建築。北坡石巖陡削，石洞、亭閣錯迭，洞室相通，極盡機巧，
有酣古堂、寫妙石室、盤嵐精舍、環碧樓、一壺天地亭、小昆邱亭等。
延樓迴廊外繞漢白玉護欄，東南為倚晴樓，西南為分涼閣，分別作為漪
瀾堂的入口。登此樓可南瞻白塔，北瞰碧波。有金山江天一覽之勝。
LONG
        );
        set("exits", ([
                "southup"   : __DIR__"baita",
                "northeast" : __DIR__"dukou2",
                "southwest" : __DIR__"yuegu",
                "southeast" : __DIR__"shiqiao",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -190);
        set("coor/y", 4100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}