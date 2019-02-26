#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "中指峯" NOR);
        set("long", @LONG
這裏就是鐵掌山的最高峯——中指峯。由於山勢太高，峯頂仍存有大量
的積雪，白雪皚皚，在陽光的照射下，泛起一片耀眼的銀光。縱目遠眺，湘
西幾百裏景色盡收眼底，瀘溪，辰溪如兩條玉帶，從山下緩緩流過。遠處那
條白色的亮線，就是湘西的大江——沅江。
LONG    );

        set("exits", ([
                "southdown" : __DIR__"shanlu-9",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}