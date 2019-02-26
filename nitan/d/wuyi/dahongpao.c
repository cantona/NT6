// Room: /d/wuyi/dahongpao.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "大紅袍");
        set("long", @LONG
這裏就是卧龍潭被殺的九條惡龍的歸宿地。峽谷兩側為九座嶙峋突
兀的峯巖，猶如九條巨龍騰空欲飛，故稱“九龍窠”。大紅袍茶樹就根
植在九龍窠的巖壁上。巖頂終日有水滴落，雲嵐霧氣，滋潤着這幾株康
熙皇帝御賜紅袍披掛的“茶中之王”。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "north"      : __DIR__"path11",
                "northwest"  : __DIR__"path10",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1390);
        set("coor/y", -4950);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
