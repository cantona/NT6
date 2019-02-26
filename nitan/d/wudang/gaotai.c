#include <ansi.h>
inherit ROOM;

void create()
{
              set("short", "南巖宮高台");
        set("long", @LONG
這裏是就是南巖宮高台。高台孤懸崖側，四望臨淵，深不可測。
山風夾耳，鬆清滌面，頓覺心竅大開。武當真武劍陣就在這裏。真武
劍陣由五名五行弟子按東西南北中木金、火、水、土方位，八名八卦
弟子按乾、坤、坎、離、巽、震、艮、兑八方天、地、水、火、風、
雷、山、澤排列。
LONG );
              set("objects", ([
                   CLASS_D("wudang") +"/wuxing": 5,
                   CLASS_D("wudang") +"/bagua": 8,
                   CLASS_D("wudang") +"/yan": 1,
              ]));
              set("exits",([
                  "northdown" : __DIR__"nanyangong",
              ]));
              set("outdoors", "wudang");
        set("coor/x", -360);
        set("coor/y", -340);
        set("coor/z", 110);
        setup();
              replace_program(ROOM);
}