// Room: /qingcheng/sanqingdian.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "三清殿");
        set("long", @LONG
古常道觀的中心是三清殿。殿中供奉三清教主：玉清原始天尊、
上清靈寶天尊和太清太上老君。原始天尊手拿圓珠，象徵洪元；靈
寶天尊懷抱太極圖，象徵混元；太上老君手持扇子，象徵太初。殿
旁有一對聯(lian)，著墨極濃。
LONG );
        set("exits", ([
                "south"    : __DIR__"tianshidong",
        ]));
        set("item_desc", ([
                "lian"    : 
"\n
     一      地
     生      法
     二      天
     二      天
     生      法
     三      道
     三      道
     生      法
     萬      自
     物      然
\n",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8100);
        set("coor/y", -900);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}