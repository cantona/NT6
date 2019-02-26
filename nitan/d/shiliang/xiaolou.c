// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "小樓");
        set("long", @LONG
這是一座精緻的小樓，你走到這裏，不由得眼前一耀，先是
聞到一陣幽幽的香氣，只見房中點着一支大紅燭，照得滿室生輝
牀上珠羅紗的帳子，白色緞被上繡着一隻黃色的鳳凰，壁上掛着
一幅工筆仕女圖。牀前桌上放着一張雕花端硯，幾件碧玉玩物，
筆筒中插了大大小小六七支筆，西首一張几上供着一盆蘭花，架
子上停着一隻白鸚鵡。滿室錦繡，連椅子上也繡了花。東邊放着
把琴，一位小姐心不在焉地坐在琴的前面。
LONG
        );
        set("exits", ([ 
            "down" : __DIR__"xiaoting",
        ]));
        set("objects", ([
                __DIR__"npc/wenyi" : 1,
        ]));
        set("coor/x", 1620);
        set("coor/y", -1770);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}