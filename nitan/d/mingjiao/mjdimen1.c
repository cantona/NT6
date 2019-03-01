// Room: /d/mingjiao/mjdimen1.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

string look_pai();

void create()
{
    set("short", "門口");
        set("long", @LONG
前面就是明教的『地字門』了，這裡是明教中女弟子修煉的地方，
從門口看進去，綾羅幔影，身姿綽綽。雖是江湖兒女，卻也不讓男子
隨意進入。門口還立有一塊木牌(mu pai)。
LONG );
    set("exits", ([
        "enter" : __DIR__"nushe",
        "southwest" : __DIR__"mjdimen",
    ]));
    set("item_desc",(["mu pai" : (: look_pai :),]));
    set("outdoors", "mingjiao");
    set("no_clean_up", 0);
    setup();
//    replace_program(ROOM);
}

string look_pai()
{
        return
        "\n"
        "※※※※※※※※※※※※※※※※※※\n"
        "※                                ※\n"
        "※  擅闖女舍者，投入碧水寒潭受罰。※\n"
        "※                                ※\n"
        "※         明教刑堂堂主冷謙 立    ※\n"
        "※                                ※\n"
        "※※※※※※※※※※※※※※※※※※\n";

}