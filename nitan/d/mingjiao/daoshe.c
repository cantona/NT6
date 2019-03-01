// Room: /d/mingjiao/daoshe.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

string look_dui();

void create()
{
    set("short", "道家竹舍");
        set("long", @LONG
走進這間竹舍，一陣香茗醉人，只見幾位白衣道人正在品茶論道，
幾個青衣小童侍立兩旁。中間那位道人中等年紀，仙風道骨，飄然而
立，身後掛有一幅對聯(dui lian)，乃是明教一位先輩李逍遙所書。
LONG );
    set("exits", ([
        "north" : __DIR__"mjfengmen1",
    ]));
    set("item_desc",(["dui lian" : (: look_dui :),]));
    set("no_clean_up", 0);
    set("no_fight", 1);
    set("sleep_room", 1);
    setup();
}

string look_dui()
{
        return
        "\n"
    "    ※※※※※※※※※※※※※※※※※※※※\n"
    "    ※※　　　※※※※※※※※※※　　　※※\n"
    "    ※※　山　※※※※※※※※※※　水　※※\n"
    "    ※※　　　※※※※※※※※※※　　　※※\n"
    "    ※※  色  ※※※※※※※※※※  光　※※\n"
    "    ※※　　　※※※※※※※※※※　　　※※\n"
    "    ※※  空  ※※※※※※※※※※  瀲　※※\n"
    "    ※※　　　※※※※※※※※※※　　　※※\n"
    "    ※※  蒙  ※※※※※※※※※※  灩　※※\n"
    "    ※※　　　※※※※※※※※※※　　　※※\n"
    "    ※※　雨　※※※※※※※※※※  晴  ※※\n"
    "    ※※　    ※※※※※※※※※※      ※※\n"
    "    ※※　亦  ※※※※※※※※※※  方  ※※\n"
    "    ※※      ※※※※※※※※※※      ※※\n"
    "    ※※  奇  ※※※※※※※※※※  好　※※\n"
    "    ※※      ※※※※※※※※※※      ※※\n"
    "    ※※※※※※※※※※※※※※※※※※※※\n";
}